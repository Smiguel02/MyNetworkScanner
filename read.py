def getIP()
    info = os.popen('ifconfig').read()

    print(info)


def getPackageManager()
    
    ID_LIKE = "debian"

    switch(N)
    {
        case 1: return "apt" if ID_LIKE == "debian"
        break;
        case 2: return "pacman -S" if ID_LIKE == "arch"
        break;
        case 3: return "pacman -S" if ID_LIKE == "red hat"
        break;
        default: return -1
    }

#------------------------------------------------------------


getIP()
manager = getPackageManager()