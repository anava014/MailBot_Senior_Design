import time
import globalVariables

rows = 3
columns = 6

cityContents = [['0' for x in range(rows)] for x in range(columns)]
cityAddresses = [['0' for x in range(rows)] for x in range(columns)]

def setContent(i,j, x):
    cityContents[i][j] = x

def returnContent(i,j):
    return cityContents[i][j]

def returnLocationIndeces(i,j):
    return cityAddresses[i][j]

def returnLocation(memAdd):
    for j in range(rows):
        for i in range(columns):
            if cityAddresses[i][j] == memAdd:
                return [i,j]

def setupContents():
    for j in range(rows):
        for i in range(columns):
            if cityContents[i][j] < 10:
                cityContents[i][j] = "0" + cityContents[i][j]

    for i in range(columns):
        cityContents[i][0] = " "
    for i in range(rows):
        cityContents[0][i] = " "

    for i in range(rows-1):
        cityContents[columns-1][i+1] = " "

def setupAddresses():
    for i in range(columns):
        cityAddresses[i][0] = "  "
    for i in range(rows):
        cityAddresses[0][i] = "  "

    for i in range(rows):
        cityAddresses[columns-1][i] = "  "

    cityAddresses[1][1] = "10"
    cityAddresses[2][1] = "11"
    cityAddresses[3][1] = "12"
    cityAddresses[4][1] = "13"

    cityAddresses[1][2] = "20"
    cityAddresses[2][2] = "21"
    cityAddresses[3][2] = "22"
    cityAddresses[4][2] = "23"


def printContents():
    print "Contents"

    print "----------------------------------------"
    for j in range(rows):
        for i in range(columns):
            print cityContents[i][j],"|", # comma works for no new line..
        print ""
    print "----------------------------------------"


def printAddresses():
    print "Addresses"

    print "----------------------------------------"
    for j in range(rows):
        for i in range(columns):
            print cityAddresses[i][j],"|", # comma works for no new line..
        print ""
    print "----------------------------------------"
