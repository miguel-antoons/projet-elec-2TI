import serial 
import serial.tools.list_ports
from termcolor import colored

ser = serial.Serial('COM3', baudrate=9600, timeout=1)


while 1:
    com = ser.readline().decode('ascii')
    if len(com) != 0:
        if int(com) > 3:
             print(colored(f"Attention : Il y a {com} personnes dans la pièce", 'red'))
             ser.write(b"1") # permet d'allumer la led rouge 
        
        else: 
            print(colored(f"Il y a {com} personnes dans la pièce" if int(com) > 1 else f"Il y a {com} personne dans la pièce", 'green'))
            ser.write(b"0") # permet d'allumer la led verte


