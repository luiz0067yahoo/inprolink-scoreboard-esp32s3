import serial
import time

try:
    s = serial.Serial('COM7', 115200, timeout=1)
    time.sleep(0.5)
    data = s.read(2048)
    print("SERIAL_READ:")
    print(data.decode('utf-8', errors='replace'))
    s.close()
except Exception as e:
    print("ERROR:", e)
