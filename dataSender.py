import serial.tools.list_ports
import time
from tkinter import *
import tkinter as tk

# Defining the variables we'll use in our script
motRun = "1" 
indexA =  "A"
indexB =  "B"
indexC =  "C"
indexD =  "D"

newLine = "\n"

# Here we are defining the serial port and opening up before sending any data
serialInst = serial.Serial() 

portVal = "/dev/cu.usbmodem11101"
print(f"Selecting port {portVal}")

serialInst.baudrate = 9600
serialInst.port = portVal

serialInst.open()

# Functions we'll use when we press the button

# Sending the data to Serial Port
def sendData(motDir):
    serialInst.write(motRun.encode('utf-8'))
    serialInst.write(indexA.encode('utf-8'))

    motSpeedInt = slider.get()
    motSpeed = str(motSpeedInt)
    serialInst.write(motSpeed.encode('utf-8'))
    serialInst.write(indexB.encode('utf-8'))

    motAngle = angleSet.get()
    if motAngle != "":
        serialInst.write(motAngle.encode('utf-8'))
        serialInst.write(indexC.encode('utf-8'))
    else:
        textAngle.config(text = "Please input angle")
        root.after(1000, textAngleReset)
        print("Please input angle")
    
    serialInst.write(motDir.encode('utf-8'))
    serialInst.write(indexD.encode('utf-8'))
    
    serialInst.write(newLine.encode('utf-8'))

    confirmTransfer()

    print("Data Sent")

# Showing confirmation message that the data has been sent in GUI
def confirmTransfer():
    canvas.itemconfig(confirm_text, text = "Data Sent")
    root.after(1000, confirmTransferReset)

# Resetting the confirmation message 
def confirmTransferReset():
    canvas.itemconfig(confirm_text, text = "")

# Resetting the message that request the user to input angle
def textAngleReset():
    textAngle.config(text = "")

# Functions to enable clockwise and anticlockwise rotation and 
# to initiate the transmission of data to serial
def RotateClockwise():
    motDir = "Clockwise"
    sendData(motDir)

def RotateAnticlockwise():
    motDir = "Anticlockwise"
    sendData(motDir)


# Here we are defining the GUI and associating the GUI widgets to functions
root = Tk()
root.title("Arduino Controller")

wth = 350
hgt = 255

# creating the image for the GUI
motor_img = PhotoImage(file = "StepperMotor_ROHS.png")
canvas = Canvas(width = wth, height = hgt)
canvas.create_image(wth/2, hgt/2, image = motor_img)
canvas.grid(row = 0, column = 0, columnspan=2)
confirm_text = canvas.create_text(wth/2, hgt/2, text = "", fill = "red", font = ("Courier", 20, "bold"))

# Creating a label and slider to control the speed of the motor
speedLabel = Label(root, text = "Speed (in RPM)")
speedLabel.grid(row=1,column=0)
slider = Scale(root, from_ = 1, to = 9, length=300, tickinterval = 1, orient=HORIZONTAL)
slider.set(4)
slider.grid(row = 2, column=0, columnspan=2)

# Creating a label and entry box to set the angle of rotation for the motor
angleLabel = Label(root, text = "Angle (in deg)")
angleLabel.grid(row=3,column=0)
angleSet = Entry(root, width=10)
angleSet.grid(row=3,column = 1)

# Creating the text box, which activate when no angle input available 
textAngle = Label(root, text = "", fg = "red")
textAngle.grid(row=4, column=1)

# Creating the buttons to set the direction of the rotation and to 
# transmit data to the serial
btn_forward = tk.Button(root, text = "Clockwise", command=RotateClockwise)
btn_forward.grid(row=5, column=0)

btn_backward = tk.Button(root, text = "Anticlockwise", command=RotateAnticlockwise)
btn_backward.grid(row=5, column=1)

# Defining the size of the window and looping through to maintain the interface
root.geometry("350x450")
root.mainloop()