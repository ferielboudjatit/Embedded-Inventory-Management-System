import serial
import re
import csv
import pyperclip
from datetime import datetime
import os

# Global variable to track current mode
current_mode = "read"  # Default to read mode

def extract_uid_from_message(message):
    """Extract UID from board or badge messages only during appropriate operations"""
    global current_mode
    
    # Update current mode based on button press messages
    if "1. Tap a board's tag to read its content" in message:
        current_mode = "read"
    elif "2. Tap a board's tag to write an entry to stock" in message:
        current_mode = "write"
    elif "2. Tap a board's tag to write an exit from stock" in message:
        current_mode = "write"
    elif "3. Tap a badge to read the ID" in message:
        current_mode = "badge"  # Badge mode is always for reading
    
    # Pattern for "Badge tag found. UID: XXXXXXXX" - badges are always just for reading ID
    badge_match = re.search(r'Badge tag found\. UID: ([A-F0-9]+)', message)
    if badge_match:
        return "badge", badge_match.group(1)
    
    # Pattern for "Board tag found. UID: XXXXXXXXXXXXXXXX" - only log if in read mode
    board_match = re.search(r'Board tag found\. UID: ([A-F0-9]+)', message)
    if board_match and current_mode == "read":
        return "board", board_match.group(1)
    
    return None, None

def save_to_csv(tag_type, uid, filename="nfc_tags.csv"):
    """Save tag data to CSV file"""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    # Check if file exists to determine if we need headers
    file_exists = os.path.exists(filename)
    
    with open(filename, 'a', newline='') as csvfile:
        fieldnames = ['timestamp', 'type', 'uid']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        # Write header if file is new
        if not file_exists:
            writer.writeheader()
        
        # Write the data
        writer.writerow({
            'timestamp': timestamp,
            'type': tag_type,
            'uid': uid
        })

def copy_to_clipboard(tag_type, uid):
    """Copy UID to clipboard"""
    clipboard_text = f"{tag_type.upper()}: {uid}"
    pyperclip.copy(clipboard_text)
    print(f"Copied to clipboard: {clipboard_text}")

try:
    ser = serial.Serial('COM19', 115200, timeout=1)  
    print("Serial port opened successfully.")
    print("Monitoring for NFC tags... (Press Ctrl+C to stop)")
    print("CSV file: nfc_tags.csv")
    print("-" * 50)
    
    while ser.is_open:
        try:
            message = ser.readline().decode('utf-8').strip()
            if message:  # Only process non-empty messages
                print(f"Received: {message}")
                
                # Check if message contains UID information
                tag_type, uid = extract_uid_from_message(message)
                
                if tag_type and uid:
                    print(f"Detected {tag_type.upper()} UID: {uid}")
                    
                    # Save to CSV
                    save_to_csv(tag_type, uid)
                    print(f"Saved to CSV: {tag_type} - {uid}")
                    
                    # Copy to clipboard
                    copy_to_clipboard(tag_type, uid)
                    
                    print("-" * 50)
                    
        except UnicodeDecodeError:
            # Skip messages that can't be decoded
            continue
            
except KeyboardInterrupt:
    print("\nStopping...")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")

finally:
    try:
        if ser.is_open:
            ser.close()
            print("Serial port closed.")
    except:
        pass