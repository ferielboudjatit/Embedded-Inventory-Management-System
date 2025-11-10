import csv
import serial
import re
import os
import shutil
import time
from typing import Optional, List
from pathlib import Path


USERPROFILE = os.environ.get('USERPROFILE')
# Modify the following paths as needed
LOCAL_FOLDER = os.path.join(USERPROFILE, "Database_update", "Database")
FURNITURES_CSV = os.path.join(LOCAL_FOLDER, 'Furnitures_Automated.csv')
NUCLEO_CSV = os.path.join(LOCAL_FOLDER, 'NUCLEO_Automated.csv')
DISCOVERY_EVAL_CSV = os.path.join(LOCAL_FOLDER, 'DISCOVERY-EVAL_Automated.csv')
USERMAP_CSV = os.path.join(LOCAL_FOLDER, 'User_map.csv')

SHAREPOINT_FOLDER = os.path.join(USERPROFILE, "OneDrive - STMicroelectronics", "EMEA MCD - Internship_folder")
SHAREPOINT_FURNITURES_CSV = os.path.join(SHAREPOINT_FOLDER, 'Furnitures_Automated.csv')
SHAREPOINT_NUCLEO_CSV = os.path.join(SHAREPOINT_FOLDER, 'NUCLEO_Automated.csv')
SHAREPOINT_DISCOVERY_EVAL_CSV = os.path.join(SHAREPOINT_FOLDER, 'DISCOVERY-EVAL_Automated.csv')
SHAREPOINT_USERMAP_CSV = os.path.join(SHAREPOINT_FOLDER, 'User_map.csv')


COM_PORT = 'COM9'

def copy_to_sharepoint(local_file: str, sharepoint_file: str, max_retries: int = 3) -> bool:
    for attempt in range(max_retries):
        try:
            os.makedirs(os.path.dirname(sharepoint_file), exist_ok=True)
            
            shutil.copy2(local_file, sharepoint_file)
            return True
            
        except (PermissionError, OSError, IOError) as e:
            print(f"Attempt {attempt + 1} failed to copy {os.path.basename(local_file)}: {e}")
    return False

def sync_all_csvs_to_sharepoint():

    files_to_copy = [
        (FURNITURES_CSV, SHAREPOINT_FURNITURES_CSV),
        (NUCLEO_CSV, SHAREPOINT_NUCLEO_CSV),
        (DISCOVERY_EVAL_CSV, SHAREPOINT_DISCOVERY_EVAL_CSV),
        (USERMAP_CSV, SHAREPOINT_USERMAP_CSV)
    ]
    
    for local_file, sharepoint_file in files_to_copy:
        if os.path.exists(local_file):
            copy_to_sharepoint(local_file, sharepoint_file)
        else:
            print(f"Warning: Local file {local_file} does not exist")
    


def read_csv(file_path: str) -> List[List[str]]:
    
    if not os.path.exists(file_path):
        print(f"Warning: {file_path} does not exist")
        return []
    
    with open(file_path, 'r', newline='', encoding='utf-8') as file:
        reader = csv.reader(file)
        return list(reader)

def write_csv(file_path: str, data: List[List[str]]) -> None:

    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    
    with open(file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerows(data)

def update_spreadsheet(user_uid: Optional[str], board_uid: str, stock_state: int):
    furnitures_data = read_csv(FURNITURES_CSV)
    nucleo_data = read_csv(NUCLEO_CSV)
    discovery_eval_data = read_csv(DISCOVERY_EVAL_CSV)
    users_data = read_csv(USERMAP_CSV)
    
    if not furnitures_data:
        print("Error: Nucleo data CSV file is missing or empty")
        return
    if not nucleo_data:
        print("Error: Nucleo data CSV file is missing or empty")
        return    
    if not discovery_eval_data:
        print("Error: Nucleo data CSV file is missing or empty")
        return    
    if not users_data:
        print("Error: Nucleo data CSV file is missing or empty")
        return

    board_name = None   # Initialize board_name to None (will store board name if found)
    # Flags to track if tables was modified
    nucleo_modified = False 
    discovery_eval_modified = False
    furnitures_modified = False

    #####################################################################
    # NUCLEO DATA CSV

    # Loop through nucleo_data starting from row index 1 (skipping header row at index 0)
    # i is the index in nucleo_data, row is the row content (list)
    # The same comments apply to the other CSV sheets

    for i, row in enumerate(nucleo_data[1:], start=1): 
        # Check if column 4 (5th column, zero-based index) matches the board_uid
        if row[4] == board_uid:
            # Set column 5 (6th column) to 'Y' if stock_state == 1 else 'N'
            nucleo_data[i][5] = 'Y' if stock_state == 1 else 'N'
            # Save the board name from column 2 (3rd column)
            board_name = row[3]
            nucleo_modified = True
            break


    user_name = None
    if user_uid and nucleo_modified:
        # Loop through users_table starting from row 1 (skip header)
        for row in users_data[1:]: 
            # Compare user_uid with column 1 (2nd column) of users_table (converted to string)
            if str(row[1]) == str(user_uid):
                # If match found, save user name from column 0 (1st column)
                user_name = row[0]
                break
        if user_name != None:
            print("Username:", user_name)

    if nucleo_modified:
        for i, row in enumerate(nucleo_data[1:], start=1):
            if row[4] == board_uid:
                # Set column 6 (7th column) to user_name if stock_state == 2, else empty string
                nucleo_data[i][6] = user_name if stock_state == 2 else ''
                break

    write_csv(NUCLEO_CSV, nucleo_data)

    #####################################################################
    # DISCOVERY EVAL DATA CSV
    for i, row in enumerate(discovery_eval_data[1:], start=1): 
        if row[4] == board_uid:
            discovery_eval_data[i][5] = 'Y' if stock_state == 1 else 'N'
            board_name = row[3]
            discovery_eval_modified = True
            break


    #user_name = None
    if user_uid and discovery_eval_modified:
        for row in users_data[1:]: 
            if str(row[1]) == str(user_uid):
                user_name = row[0]
                break
        if user_name != None:
            print("Username:", user_name)

    if discovery_eval_modified:
        for i, row in enumerate(discovery_eval_data[1:], start=1):
            if row[4] == board_uid:
                discovery_eval_data[i][6] = user_name if stock_state == 2 else ''
                break

    write_csv(DISCOVERY_EVAL_CSV, discovery_eval_data)

    #####################################################################
    # FURNITURES DATA
    for i, row in enumerate(furnitures_data[1:], start=1): 
        if row[4] == board_uid:
            furnitures_data[i][5] = 'Y' if stock_state == 1 else 'N'
            board_name = row[3]
            furnitures_modified = True
            break
   

    #user_name = None
    if user_uid and furnitures_modified:
        for row in users_data[1:]: 
            if str(row[1]) == str(user_uid):
                user_name = row[0]
                break
        if user_name != None:
            print("Username:", user_name)

    if furnitures_modified:
        for i, row in enumerate(furnitures_data[1:], start=1):
            if row[4] == board_uid:
                furnitures_data[i][6] = user_name if stock_state == 2 else ''
                break


    print("Board name:", board_name)

    write_csv(FURNITURES_CSV, furnitures_data)    

    sync_all_csvs_to_sharepoint()


    

sync_all_csvs_to_sharepoint()    
ser = serial.Serial(COM_PORT, 115200, timeout=1)
pattern_in = r"Received Buffer: Message board got into stock : ([0-9A-F]+)_(\d)"
pattern_out = r"Received Buffer: Message board got out of stock : ([0-9A-F]+)_([0-9A-F]+)_(\d)"
try:
    while ser.is_open:

        message = ser.readline().decode('utf-8').strip()
        if message :
            match_in = re.match(pattern_in, message)
            match_out = re.match(pattern_out, message)
            print(message)
            if match_in:
                user_uid = None
                board_uid = match_in.group(1)
                stock_state = int(match_in.group(2))
                print(f"Board UID: {board_uid}, Stock State: {stock_state}")
                update_spreadsheet(user_uid = None, board_uid=board_uid, stock_state=stock_state)
            elif match_out:
                user_uid = match_out.group(1)
                board_uid = match_out.group(2)
                stock_state = int(match_out.group(3))
                print(f"User UID: {user_uid}, Board UID: {board_uid}, Stock State: {stock_state}")
                update_spreadsheet(user_uid = user_uid, board_uid = board_uid, stock_state = stock_state)

except serial.SerialException as e:
    print(f"Error reading from serial port: {e}")
finally:
    if ser.is_open:
        ser.close()
        print("Serial port closed.")
