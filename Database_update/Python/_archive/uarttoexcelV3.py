import csv
import serial
import re
import os
import shutil
import time
from typing import Optional, List
from pathlib import Path

LOCAL_FOLDER = r"C:\\Users\\boudjatf\\Downloads\\Database\\Updated\\"  
NUCLEO_CSV = os.path.join(LOCAL_FOLDER, 'NUCLEO.csv')
USERS_CSV = os.path.join(LOCAL_FOLDER, 'Users.csv')
ROAMING_CSV = os.path.join(LOCAL_FOLDER, 'Roaming.csv')

SHAREPOINT_FOLDER = r"C:\\Users\\boudjatf\\OneDrive - STMicroelectronics\\EMEA MCD - Internship_folder\\"  

SHAREPOINT_NUCLEO = os.path.join(SHAREPOINT_FOLDER, 'NUCLEO.csv')
SHAREPOINT_USERS = os.path.join(SHAREPOINT_FOLDER, 'Users.csv')
SHAREPOINT_ROAMING = os.path.join(SHAREPOINT_FOLDER, 'Roaming.csv')

def copy_to_sharepoint(local_file: str, sharepoint_file: str, max_retries: int = 3) -> bool:
    for attempt in range(max_retries):
        try:
            os.makedirs(os.path.dirname(sharepoint_file), exist_ok=True)
            
            shutil.copy2(local_file, sharepoint_file)
            print(f"Successfully copied {os.path.basename(local_file)} to SharePoint")
            return True
            
        except (PermissionError, OSError, IOError) as e:
            print(f"Attempt {attempt + 1} failed to copy {os.path.basename(local_file)}: {e}")
            if attempt < max_retries - 1:
                time.sleep(2)  
            else:
                print(f"Failed to copy {os.path.basename(local_file)} after {max_retries} attempts")
                return False
    return False

def sync_all_csvs_to_sharepoint():

    files_to_copy = [
        (NUCLEO_CSV, SHAREPOINT_NUCLEO),
        (USERS_CSV, SHAREPOINT_USERS),
        (ROAMING_CSV, SHAREPOINT_ROAMING)
    ]
    
    success_count = 0
    for local_file, sharepoint_file in files_to_copy:
        if os.path.exists(local_file):
            if copy_to_sharepoint(local_file, sharepoint_file):
                success_count += 1
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

    nucleo_data = read_csv(NUCLEO_CSV)
    users_data = read_csv(USERS_CSV)
    roaming_data = read_csv(ROAMING_CSV)
    
    if not nucleo_data or not users_data or not roaming_data:
        print("Error: One or more CSV files are missing or empty")
        return
    
    board_name = None
    nucleo_modified = False
    
    for i, row in enumerate(nucleo_data[1:], start=1): 
        if len(row) > 4 and row[4] == board_uid:

            if len(row) > 5:
                nucleo_data[i][5] = 'Y' if stock_state == 1 else 'N'
            else:
                nucleo_data[i].extend([''] * (6 - len(row)))
                nucleo_data[i][5] = 'Y' if stock_state == 1 else 'N'
            
            if len(row) > 2:
                board_name = row[2]
            nucleo_modified = True
            break
    
    print("Board name:", board_name)
    
    user_name = None
    if user_uid:
        for row in users_data[1:]: 
            if len(row) > 1 and str(row[1]) == str(user_uid):
                user_name = row[0]
                break
        if user_name:
            print("Username:", user_name)
    
    if nucleo_modified:
        for i, row in enumerate(nucleo_data[1:], start=1):
            if len(row) > 4 and row[4] == board_uid:
                if len(row) <= 6:
                    nucleo_data[i].extend([''] * (7 - len(row)))
                nucleo_data[i][6] = user_name if stock_state == 2 else ''
                break
    
    roaming_modified = False
    if board_name and roaming_data:
        header_row = roaming_data[0] if roaming_data else []
        
        for i, row in enumerate(roaming_data[1:], start=1):
            if len(row) > 1 and str(row[1]) == str(board_name):
                for col_idx in range(2, len(header_row)):
                    column_header = header_row[col_idx]
                    
                    while len(roaming_data[i]) <= col_idx:
                        roaming_data[i].append('')
                    
                    if stock_state == 2: 
                        if column_header == user_name:
                            roaming_data[i][col_idx] = '1'
                            roaming_modified = True
                    elif stock_state == 1:  
                        if roaming_data[i][col_idx] == '1':
                            roaming_data[i][col_idx] = '0'
                            roaming_modified = True
    
    
    files_updated = []
    if nucleo_modified:
        write_csv(NUCLEO_CSV, nucleo_data)
        files_updated.append("NUCLEO")
        
    
    if roaming_modified:
        write_csv(ROAMING_CSV, roaming_data)
        files_updated.append("ROAMING")
        
    

    if files_updated:
        sync_all_csvs_to_sharepoint()


    

sync_all_csvs_to_sharepoint()    
ser = serial.Serial('COM9', 115200, timeout=1)
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
