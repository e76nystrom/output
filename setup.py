#!/cygdrive/c/Python37/Python.exe

import os
import re

expList = []
tmp = open(".files", "r")
for l in tmp:
    l = l.strip()
    print(l)
    l = l.replace(".", "\.")
    l = l.replace("*", ".+?")
    l += "$"
    print(l)
    expList.append(re.compile(l))
tmp.close()

files = os.listdir(".")
ignoreList = {}
dirList = []
for f in files:
    if f[-1] == "~":
        continue
    match = False
    # print(f)
    for prog in expList:
        result = prog.match(f)
        if result != None:
            match = True
    if match:
        print(f)
    else:
        if os.path.isdir(f):
            print("%s is directory" % (f))
            dirList.append(f + "/*")
        else:
            if f.startswith('.'):
                dirList.append(f)
            else:
                fileParts = f.split('.')
                ext = fileParts[-1]
                if ext in ignoreList:
                    pass
                else:
                    ignoreList[ext] = 1

for d in dirList:
    print(d)

for key in ignoreList:
    print("*.%s" % (key))
