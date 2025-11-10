import csv
import serial
import re
import os
from typing import Optional, List, Dict, Any

# Define CSV file paths
NUCLEO_CSV = 'C:\\Users\\boudjatf\\Downloads\\Database\\Updated\\NUCLEO.csv'
USERS_CSV = 'C:\\Users\\boudjatf\\Downloads\\Database\\Updated\\Users.csv'
ROAMING_CSV = 'C:\\Users\\boudjatf\\Downloads\\Database\\Updated\\Roaming.csv'

def read_csv(file_path: str) -> List[List[str]]:

    if not os.path.exists(file_path):
        print(f"Warning: {file_path} does not exist")
        return []
    
    with open(file_path, 'r', newline='', encoding='utf-8') as file:
        reader = csv.reader(file)
        return list(reader)

def write_csv(file_path: str, data: List[List[str]]) -> None:

    with open(file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerows(data)

def update_spreadsheet(user_uid: Optional[str], board_uid: str, stock_state: int):
    # Read all CSV files
    nucleo_data = read_csv(NUCLEO_CSV)
    users_data = read_csv(USERS_CSV)
    roaming_data = read_csv(ROAMING_CSV)
    
    if not nucleo_data or not users_data or not roaming_data:
        print("Error: One or more CSV files are missing or empty")
        return
    
    # Find board name from NUCLEO sheet (assuming column indices: 0,1,2,3,4,5,6...)
    # Column 4 = board_uid, Column 5 = stock status, Column 2 = board_name, Column 6 = user assignment
    board_name = None
    nucleo_modified = False
    
    for i, row in enumerate(nucleo_data[1:], start=1):  # Skip header row
        if len(row) > 4 and row[4] == board_uid:
            # Update stock status (column 5): 'Y' if stock_state == 1, 'N' otherwise
            if len(row) > 5:
                nucleo_data[i][5] = 'Y' if stock_state == 1 else 'N'
            else:
                nucleo_data[i].extend([''] * (6 - len(row)))  # Extend row if needed
                nucleo_data[i][5] = 'Y' if stock_state == 1 else 'N'
            
            # Get board name (column 2)
            if len(row) > 2:
                board_name = row[2]
            nucleo_modified = True
            break
    
    print("Board name:", board_name)
    
    # Find user name from Users sheet (assuming column 0 = user_name, column 1 = user_uid)
    user_name = None
    if user_uid:
        for row in users_data[1:]:  # Skip header row
            if len(row) > 1 and str(row[1]) == str(user_uid):
                user_name = row[0]
                break
        if user_name:
            print("Username:", user_name)
    
    # Update user assignment in NUCLEO sheet (column 6)
    if nucleo_modified:
        for i, row in enumerate(nucleo_data[1:], start=1):
            if len(row) > 4 and row[4] == board_uid:
                # Ensure row has enough columns
                if len(row) <= 6:
                    nucleo_data[i].extend([''] * (7 - len(row)))
                # Set user assignment: user_name if stock_state == 2, empty otherwise
                nucleo_data[i][6] = user_name if stock_state == 2 else ''
                break
    
    # Update Roaming sheet
    roaming_modified = False
    if board_name and roaming_data:
        # Get header row to find column indices
        header_row = roaming_data[0] if roaming_data else []
        
        for i, row in enumerate(roaming_data[1:], start=1):  # Skip header row
            if len(row) > 1 and str(row[1]) == str(board_name):
                # Process columns starting from column 2 (index 2)
                for col_idx in range(2, len(header_row)):
                    column_header = header_row[col_idx]
                    
                    # Ensure row has enough columns
                    while len(roaming_data[i]) <= col_idx:
                        roaming_data[i].append('')
                    
                    if stock_state == 2:  # User taking board
                        if column_header == user_name:
                            roaming_data[i][col_idx] = '1'
                            roaming_modified = True
                    elif stock_state == 1:  # Board returned to stock
                        # Reset all user assignments for this board
                        if roaming_data[i][col_idx] == '1':
                            roaming_data[i][col_idx] = '0'
                            roaming_modified = True
    
    # Save modified data back to CSV files
    if nucleo_modified:
        write_csv(NUCLEO_CSV, nucleo_data)
        print("Updated NUCLEO CSV")
    
    if roaming_modified:
        write_csv(ROAMING_CSV, roaming_data)
        print("Updated ROAMING CSV")

ser = serial.Serial('COM9', 115200, timeout=1)
pattern_in = r"Received Buffer: Message board got into stock : ([0-9A-F]+)_(\d)"
pattern_out = r"Received Buffer: Message board got out of stock : ([0-9A-F]+)_([0-9A-F]+)_(\d)"
try:
    while ser.is_open:
        #user_uid = None
        #board_uid = None
        #stock_state = None
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
            #else:
                #break
        #else:
            #time.sleep(10000)
            #break
                update_spreadsheet(user_uid = user_uid, board_uid = board_uid, stock_state = stock_state)

except serial.SerialException as e:
    print(f"Error reading from serial port: {e}")
finally:
    if ser.is_open:
        ser.close()
        print("Serial port closed.")
