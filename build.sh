#!/bin/bash

./asetup.py output
cp *.cpp src/
cp *.h src/
cp output.ino src/main.cpp

PATH=/cygdrive/c//Users/Eric/.platformio/penv/Scripts:\
/cygdrive/c/Python39:\
/cygdrive/c/Python39/DLLs:\
/cygdrive/c/Python39/Scripts \
HOME=C:/Users/Eric platformio run

rm -f *.lst
f=.pio/build/mega2560/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputMega.lst
fi

f=.pio/build/pro16MHzatmega328/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputMini.lst
fi

f=.pio/build/sparkfun_promicro16/firmware.elf
if [ -e $f ]; then
 avr-objdump.exe -l -d $f >outputProMicro.lst
fi
