#!/cygdrive/c/Python37/Python.exe
#!/cygdrive/c/DevSoftware/Python/Python36-32/Python.exe

from sys import argv, stdout
from os.path import dirname, isfile, realpath
from os import getcwd
#from imp import load_source
import importlib
import os 

debug = False

class config():
    def __init__(self):
        self.init()

    def init(self):
        self.pins = {}
        self.analog = {}
        self.ports = {}
        self.functions = {}

    def openFiles(self, fName):
        self.h = open(fName + '.h', 'w')
        self.h.write("extern void pinConfig();\n\n")

        cpp = open(fName + '.cpp', 'w')
        self.cpp = cpp
        cpp.write("#include <Arduino.h>\n")
        cpp.write("#include \"%s.h\"\n" % (fName))
        if debug:
            cpp.write("#include \"serial.h\"\n")
        cpp.write("\nvoid pinConfig()\n{\n")

    def closeFiles(self):
        self.h.close()

        self.cpp.write("}\n")
        self.cpp.close()

    def readPins(self, pinList):
        self.pins = {}
        self.ports = {}
        for i in range(len(pinList)):
            data = pinList[i]
            (pin, port) = data
            self.pins[pin] = port
            self.ports[port] = pin
            # print("pin %2d port %s" % (pin, port))

    def readAlt(self, altList):
        self.functions = {}
        for i in range(len(altList)):
            data = altList[i]
            (function, port) = data
            try:
                pin = int(self.ports[port])
            except KeyError:
                pin = -1
            self.functions[function] = port
            # print("function %6s port %s pin %d" % (function, port, pin))
            if function.startswith("OC"):
                p = port[1:2]
                portName = "PIN" + p
                portMask = "_BV(" + port + ")"
                h = self.h
                h.write("#define %s_Port %s\n" % (function, portName))
                h.write("#define %s_Mask %s\n" % (function, portMask))
                h.write("\n")

    def varName(self, name):
        varName = name.lower()
        tmp = varName.split("_")
        if len(tmp) > 1:
            varName = ""
            first = True
            for s in tmp:
                if first:
                    varName = s.lower()
                    first = False
                else:
                    varName = varName + s[0].upper() + s[1:].lower()
        return(varName)

    def outPin(self):
        h = self.h
        if not self.pin in self.pins:
            h.write(("#define %sRead() 0\n" % \
                        (self.funcName)))
            h.write(("#define %sSet()\n" % \
                        (self.funcName)))
            h.write(("#define %sClr()\n" % \
                        (self.funcName)))
            return

        if debug:
            self.cpp.write(" puts(F(\"%-10s %2d %s out\\n\"));\n" % \
                           (self.name, self.pin, self.port));
        self.cpp.write(" pinMode(%s, OUTPUT);\n" % (self.configPin))
        h.write("#define %s %s\n" % (self.configPin, self.pin))
        h.write("#define %s %s\n" % (self.configPort, self.portName))
        h.write("#define %s %s\n" % (self.configDDR, self.portDDR))
        h.write("#define %s %s\n" % (self.configIn, self.portIn))
        h.write("#define %s_Bit %s\n" % (self.name, self.port))
        h.write("#define %s %s\n" % (self.configMask, self.portMask))

        (t0, t1, t2) = ('=', '&= ~', '|= ') if 'low' in self.options else \
            ('!', '|= ', '&= ~')
        # print(self.configPin, self.options, t0, t1, t2)

        h.write(("#define %sRead() ((%s & %s) %s= 0)\n" % \
                 (self.funcName, self.configPort, self.configMask, t0)))
        h.write(("#define %sSet() %s %s%s\n" % \
                    (self.funcName, self.configPort, t1, self.configMask)))
        h.write(("#define %sClr() %s %s%s\n" % \
                    (self.funcName, self.configPort, t2, self.configMask)))

    def inPin(self, pullup=False):
        if pullup:
            mode = "INPUT_PULLUP"
        else:
            mode = "INPUT"

        if 'test' in self.options:
            mode = "OUTPUT"
            self.portIn = self.portName

        high = not ('low' in self.options)

        if debug:
            self.cpp.write(" puts(F(\"%-10s %2d %s in\\n\"));\n" % \
                      (self.name, self.pin, self.port));
        self.cpp.write(" pinMode(%s, %s);\n" % (self.configPin, mode))
        h = self.h
        h.write("#define %s %s\n" % (self.configPin, self.pin))
        h.write("#define %s %s\n" % (self.configIn, self.portIn))
        h.write("#define %s_Bit %s\n" % (self.name, self.port))
        h.write("#define %s_Mask %s\n" % (self.name, self.portMask))
        h.write("#define %sIn() ((%s & %s) != 0)\n" % \
                (self.funcName, self.configIn, self.configMask))


        h.write("#define %sSet() ((%s & %s) %s= 0)\n" % \
                (self.funcName, self.configIn, self.configMask,
                 ('=', '!')[high]))
        h.write("#define %sClr() ((%s & %s) %s= 0)\n" % \
                (self.funcName, self.configIn, self.configMask,
                 ('=', '!')[not high]))

        if 'test' in self.options:
            polarity = ('Clr', 'Set')
            h.write(("#define %sT%s() %s |= %s\n" % \
                     (self.funcName, polarity[high], self.portName, \
                      self.configMask)))
            h.write(("#define %sT%s() %s &= ~%s\n" % \
                     (self.funcName, polarity[not high], self.portName, \
                      self.configMask)))

    def extiPin(self):
        for key, val in self.functions.items():
            if val == self.port and key.startswith("INT"):
                intNum = int(key[3])
                reg = "EICR" + ("A", "B")[intNum >= 4]
                option = self.option[0].strip()
                try:
                    mask = {'low' : '0',
                            'change' : '_BV(ISC00)',
                            'falling' : '_BV(ISC01)',
                            'rising' : '_BV(ISC01)|_BV(ISC00)'}[option]
                except KeyError:
                    mask = '0'
                shift = (intNum & 3) * 2
                val = "(%s) << %d" % (mask, shift)
                stm0 = "%s &= ~((_BV(ISC01) | _BV(ISC00)) << %d)" % \
                        (reg, shift)
                stm1 = "%s |= %s" % (reg, val)
                stm2 = "EIMSK |= (_BV(INT0) << %d)" % (intNum)
                self.h.write("#define %sIntInit() %s;\\\n\t%s;\\\n\t%s\n" % \
                             (self.varName(self.name), stm0, stm1, stm2))

    def readConfig(self, config):
        used = {}
        for i in range(len(config)):
            data = config[i]
            (name, pin, direction) = data
            tmp = direction.split(",")
            self.option = None
            if len(tmp) > 1:
                direction = str(tmp[0])
                self.option = tmp[1:]
                direction = direction.strip()

            self.options = {}
            if self.option != None:
                for i in self.option:
                    self.options[i.strip()] = 1

            if pin in self.pins:
                if pin in used:
                    (first, firstDir) = used[pin]
                    if firstDir != direction:
                        print ("%s pin %d already used for %s" % \
                               (name, pin, first))
                else:
                    used[pin] = (name, direction)

            self.funcName = self.varName(name)
            if pin in self.pins:
                self.port = self.pins[pin]
                p = self.port[1:2]
                self.portName = "PORT" + p
                self.portDDR = "DDR" + p
                self.portIn = "PIN" + p
                self.configPin = name + "_Pin"
                self.configPort = name + "_Port"
                self.configDDR = name + "_DDR"
                self.configBit = name + "_Bit"
                self.configIn = name + "_In"
                self.configMask = name + "_Mask"
                self.portMask = "_BV(" + self.configBit + ")"

            self.pin = pin
            self.name = name
            if direction == "out":
                self.outPin()
            elif direction == "in":
                self.inPin()
            elif direction == "inpu":
                self.inPin(True)
            elif direction == "exti":
                self.inPin()
                self.extiPin()
            self.h.write("\n")

    def defines(self, defineDef):
        if len(defineDef) == 0:
            return
        for configDef in defineDef:
            (name, value) = configDef
            self.h.write("#define %-20s %s\n" % (name, value))
        self.h.write("\n")

if len(argv) > 1:
    fName = argv[1]
else:
    path = getcwd().split(os.sep)
    fName = path[len(path) - 1]

if not isfile(fName + ".py"):
    print("invalid file %s" % fName)
    exit()

#cfg = load_source("cfg", getcwd() + os.sep + fName + ".py")
#file = os.path.join(getcwd(), fName)# + ".py")
cfg = importlib.__import__(fName)

fName = cfg.outFile

c = config();
c.openFiles(fName)
c.defines(cfg.commonDefines)
basePath = dirname(realpath(__file__))

for info in cfg.pinConfig:
    c.init()

    procType = info['type']
    c.h.write("#ifdef %s\n\n" % (procType))
    c.cpp.write("\n#ifdef %s\n\n" % (procType))

    c.defines(info['defines'])

    boardDef = info['def']
    boardSrc=  basePath + os.sep + boardDef + ".py"
    #board = load_source("board", boardSrc)
    board = importlib.__import__(boardDef)

    c.readPins(board.digitalDef)
    c.readAlt(board.altDef)

    config = info['config']
    c.readConfig(config)

    c.cpp.write("\n#endif\n")
    c.h.write("#endif\n")

c.closeFiles()
