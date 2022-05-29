#!/bin/bash

if [[ "$OSTYPE" == "cygwin" ]]; then
 ./asetup.py output
else
 python asetup.py
fi

mkdir -p src
cp *.cpp src/
cp *.h src/
cp output.ino src/main.cpp

if [[ "$OSTYPE" == "cygwin" ]]; then
 PATH=/cygdrive/c//Users/Eric/.platformio/penv/Scripts:\
/cygdrive/c/Python39:\
/cygdrive/c/Python39/DLLs:\
/cygdrive/c/Python39/Scripts \
  HOME=C:/Users/Eric platformio run
else
 pio run
fi

if [[ "$OSTYPE" == "cygwin" ]]; then
 OBJDUMP="avr-objdump"
else
 OBJDUMP="~/.platformio/packages/toolchain-atmelavr/bin/avr-objdump"
fi

rm -f *.lst
f=.pio/build/mega2560/firmware.elf
if [ -e $f ]; then
 $OBJDUMP -l -d $f >outputMega.lst
fi

f=.pio/build/pro16MHzatmega328/firmware.elf
if [ -e $f ]; then
 $OBJDUMP -l -d $f >outputMini.lst
fi

f=.pio/build/sparkfun_promicro16/firmware.elf
if [ -e $f ]; then
 $OBJDUMP -l -d $f >outputProMicro.lst
fi
