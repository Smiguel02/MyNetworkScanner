import os

def getIP():
    info = os.popen('ifconfig').read()

    firstDelPos=info.find("inet ") + 5
    secondDelPos=info.find(" netmask") -1

    inet = info[firstDelPos:secondDelPos]

    print(info)
    print(firstDelPos)
    print(secondDelPos)

    print("|",inet,"|")
    
//de facto isto é bue util
def getPackageManager():

    mylines = []                             
    with open ('/etc/os-release', 'rt') as myfile: 
    
        for myline in myfile:
            mylines.append(myline)
    
    line = mylines[3]

    firstDelPos=line.find("\"") + 1
    secondDelPos=(line[firstDelPos]).find("\"") -1

    ID_LIKE = line[firstDelPos:secondDelPos]

    print(ID_LIKE)

    if ID_LIKE == "debian" or ID_LIKE == "ubuntu debian": return "apt"
    elif ID_LIKE == "arch": return "pacman -S"
    elif ID_LIKE == "red hat": return "yum"
    else: return -1

#------------------------------------------------------------


getIP()
manager = getPackageManager()

if manager == -1: print(Error)
else: print(manager)
