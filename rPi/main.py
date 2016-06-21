from Tkinter import *
import globalVariables
import serial
import city
import os

bluetoothSerial = serial.Serial( "/dev/rfcomm0", baudrate=9600 )

os.system("clear")
city.setupContents()
city.setupAddresses()

buttonHeight = 5

def declareFrameLabels():

	statusLabel = Label( statusFrame, textvariable=statusString, relief=RAISED ,anchor=W, height = 1, width = 70)
	statusString.set("Waiting for Set or Get Input..")
	statusLabel.pack(side = LEFT, fill=BOTH, expand=YES)


	menuString = StringVar()
	menuLabel = Label( menuFrame, textvariable=menuString, relief=RAISED, anchor=W, height = 1, width = 70)
	menuString.set("Menu")
	menuLabel.pack(side = TOP, fill=BOTH, expand=YES)


	cityString = StringVar()
	cityLabel = Label( cityFrame, textvariable=cityString, relief=RAISED, anchor=W, height = 1, width = 70)
	cityString.set("City")
	cityLabel.pack(side = TOP, fill=BOTH, expand=YES)


	entryString = StringVar()
	entryLabel = Label( entryFrame, textvariable=entryString, relief=RAISED, anchor=W, height = 1, width = 70)
	entryString.set("Input")
	entryLabel.pack(side = TOP, fill=BOTH, expand=YES)
	

def returnCellContents(cellNum):
	cellContents ="Address: "
	cellContents += str(cellNum)
	cellContents += "\nContent: "
	i,j = city.returnLocation(str(cellNum))
	cellContents += str(city.returnContent(i,j))
	return cellContents


def setCallBack():
	globalVariables.globalSetting = 's'
	tenButton['state'] = NORMAL
	elevenButton['state'] = NORMAL
	twelveButton['state'] = NORMAL
	thirteenButton['state'] = NORMAL
	twentyButton['state'] = NORMAL
	twentyOneButton['state'] = NORMAL
	twentyTwoButton['state'] = NORMAL
	twentyThreeButton['state'] = NORMAL
	setButton['state'] = DISABLED
	getButton['state'] = DISABLED
	statusString.set("Set - Waiting for Address Input..")

def getCallBack():
	globalVariables.globalSetting = 'g'
	tenButton['state'] = NORMAL
	elevenButton['state'] = NORMAL
	twelveButton['state'] = NORMAL
	thirteenButton['state'] = NORMAL
	twentyButton['state'] = NORMAL
	twentyOneButton['state'] = NORMAL
	twentyTwoButton['state'] = NORMAL
	twentyThreeButton['state'] = NORMAL
	setButton['state'] = DISABLED
	getButton['state'] = DISABLED
	statusString.set("Get - Waiting for Address Input..")

def addressCallBack(cellNum):
	statusString.set("Address: " + str(cellNum) + "- Waiting for Content of Memory..")
	tenButton['state'] = DISABLED
	elevenButton['state'] = DISABLED
	twelveButton['state'] = DISABLED
	thirteenButton['state'] = DISABLED
	twentyButton['state'] = DISABLED
	twentyOneButton['state'] = DISABLED
	twentyTwoButton['state'] = DISABLED
	twentyThreeButton['state'] = DISABLED

	if globalVariables.globalSetting == 'g':
		i,j = city.returnLocation(str(cellNum))
		statusString.set("Getting Memory..")
		#Sending coordinates to arduino
		bluetoothSerial.write('g')
		bluetoothSerial.write(str(j))
		bluetoothSerial.write(str(i))
		a = None
		while True:
			a = bluetoothSerial.read()
			if a == '1':
				break;	
		bluetoothSerial.write(city.returnContent(i,j))
	
		setButton['state'] = NORMAL
		getButton['state'] = NORMAL
		statusString.set("Waiting for Set or Get Input..")

	else:
		inputPush(cellNum)

def inputPush(cellNum):
	inputEntry['state'] = NORMAL
	globalVariables.globalAddress = cellNum
	print globalVariables.globalAddress

def updateButtonContents(i,j,x):
	location = city.returnLocationIndeces(i,j)
	cellContents ="Address: "
	cellContents += location
	cellContents += "\nContent: "
	cellContents += x

	if location == '10':
		tenButton['text'] = cellContents
	elif location == '11':
		elevenButton['text'] = cellContents
	elif location == '12':
		twelveButton['text'] = cellContents
	elif location == '13':
		thirteenButton['text'] = cellContents
	elif location == '20':
		twentyButton['text'] = cellContents
	elif location == '21':
		twentyOneButton['text'] = cellContents
	elif location == '22':
		twentyTwoButton['text'] = cellContents
	elif location == '23':
		twentyThreeButton['text'] = cellContents

def enterPressed(event=None):
	content = inputEntry.get()
	inputEntry.delete(0, END)
	inputEntry['state'] = DISABLED
	if globalVariables.globalSetting == 's':
		i,j = city.returnLocation(str(globalVariables.globalAddress))
		x = content
		statusString.set("Setting Memory..")

		#Sending commands to arduino to interpret
		bluetoothSerial.write('s')
		bluetoothSerial.write(str(j))
		bluetoothSerial.write(str(i))
		bluetoothSerial.write(str(x));
		#Wait for handshake here

		print("Setting Memory..")
		while True:
			a = bluetoothSerial.read()
			if a == '1':
				break;
		city.setContent(i,j,x)
		setButton['state'] = NORMAL
		getButton['state'] = NORMAL
		statusString.set("Waiting for Set or Get Input..")
		updateButtonContents(i,j,x)

#Main GUI Window
root = Tk()
root.geometry("800x480")
root.title("Mailman Computer Memory")

#Declaring Frames
statusString = StringVar()
statusFrame = Frame(root)
statusFrame.pack(side = TOP, fill=BOTH, expand=YES)


menuFrame = Frame(root)
menuFrame.pack( side = TOP, fill=BOTH, expand=YES)

cityFrame = Frame(root)
cityFrame.pack( side = TOP, fill=BOTH, expand=YES)
cityTwoFrame = Frame(root)
cityTwoFrame.pack( side = TOP, fill=BOTH, expand=YES)

entryFrame = Frame(root)
entryFrame.pack(side = TOP, fill=BOTH, expand=YES)


#Declaring Frame Objects
declareFrameLabels()

#Declaring Menu Buttons
setButton = Button(menuFrame, text ="Set", command = setCallBack, height = 2, width = 20)
setButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 30)

getButton = Button(menuFrame, text ="Get", command = getCallBack, height = 2, width = 20)
getButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 30)

#Declaring City Buttons
tenButton = Button(cityFrame, text =returnCellContents(10), command= lambda: addressCallBack(10), state = DISABLED, height = buttonHeight)
tenButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

elevenButton = Button(cityFrame, text = returnCellContents(11), command = lambda: addressCallBack(11), state = DISABLED, height = buttonHeight)
elevenButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

twelveButton = Button(cityFrame, text =returnCellContents(12), command = lambda: addressCallBack(12), state = DISABLED, height = buttonHeight)
twelveButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

thirteenButton = Button(cityFrame, text =returnCellContents(13), command = lambda: addressCallBack(13), state = DISABLED, height = buttonHeight)
thirteenButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

twentyButton = Button(cityTwoFrame, text =returnCellContents(20), command= lambda: addressCallBack(20), state = DISABLED, height = buttonHeight)
twentyButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

twentyOneButton = Button(cityTwoFrame, text = returnCellContents(21), command = lambda: addressCallBack(21), state = DISABLED, height = buttonHeight)
twentyOneButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

twentyTwoButton = Button(cityTwoFrame, text =returnCellContents(22), command = lambda: addressCallBack(22), state = DISABLED, height = buttonHeight)
twentyTwoButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

twentyThreeButton = Button(cityTwoFrame, text =returnCellContents(23), command = lambda: addressCallBack(23), state = DISABLED, height = buttonHeight)
twentyThreeButton.pack(side = LEFT, fill=BOTH, expand = 1, padx = 10)

inputEntry = Entry(entryFrame, state = DISABLED)
inputEntry.pack(side = LEFT, fill=BOTH, expand = 1)

inputEntry.bind('<Return>', enterPressed)

root.mainloop()




