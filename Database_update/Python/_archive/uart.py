import serial

try:
    ser = serial.Serial('COM15', 115200, timeout=1)  
    print("Serial port opened successfully.")
    
    while ser.is_open:
        message = ser.readline().decode('utf-8').strip()
        print("Received message:", message)


except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
finally:
    if ser.is_open:
        ser.close()
        print("Serial port closed.")