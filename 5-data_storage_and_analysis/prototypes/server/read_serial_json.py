import serial
import json
import keyboard

ser = serial.Serial('COM6', 9600)
while not keyboard.is_pressed('q'):
    s = ser.readline()
    print(s)
