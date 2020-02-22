#!/bin/bash

./asetup.py output
cp *.cpp src/
cp *.h src/
cp output.ino src/output_p.cpp

PATH=/cygdrive/c//Users/Eric/.platformio/penv/Scripts:\
/cygdrive/c/Python37:\
/cygdrive/c/Python37/DLLs:\
/cygdrive/c/Python37/Scripts \
HOME=C:/Users/Eric platformio run

rm -f *.lst
f=.pio/build/megaatmega2560/firmware.elf
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
