import os
import subprocess
import sys

pingList = open("ADD-PATH-TO-FILE-HERE", "r")
GREEN = '\033[0;32m'
RED = '\033[3;31m'
RESET = '\033[0;0m'
for i in pingList:
	#It's neccessary that the IP addresses are the last bits of text on each line
        ipAddr = i[-15:]
        ipAddr = ipAddr.strip(' ')
        ipAddr = ipAddr.strip('\n')
        with open(os.devnull, 'w') as DEVNULL:
                try:
                        subprocess.check_call(
                                ['ping', '-w', '1', ipAddr],
                                stdout = DEVNULL, #Suppresses output from ping command
                                stderr = DEVNULL
                        )
                        sys.stdout.write(GREEN)
                        print(ipAddr + ' is up.')
                except subprocess.CalledProcessError:
                        sys.stdout.write(RED)
                        print(ipAddr + ' is down.')

pingList.close()
DEVNULL.close()
sys.stdout.write(RESET)
