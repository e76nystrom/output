#!/bin/bash

./asetup.py output
cp *.cpp src/
cp *.h src/
cp output.ino src/output_p.cpp

PATH=/cygdrive/c/Python27:\
/cygdrive/c/Python27/DLLs:\
/cygdrive/c/Python27/Scripts:\
$PATH \
HOME=C:/Users/Eric platformio run
rm -f *.lst
f=.pioenvs/megaatmega2560/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputMega.lst
fi
f=.pioenvs/pro16MHzatmega328/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputMini.lst
fi
f=.pioenvs/sparkfun_promicro16/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputProMicro.lst
fi
