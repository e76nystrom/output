#!/bin/bash

usbtiny=0
serial=1
avrisp=0
if [ -z $1 ]
then
 port="COM20"
else
 port=$1
fi

TARGET=".pio/build/mega2560/firmware.hex:i"
echo $TARGET

AVRDUDE="/cygdrive/c/Users/Eric/.platformio/packages/tool-avrdude/avrdude"

#AVRDUDE="/cygdrive/c/Users/Eric/AppData/Local/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino14/bin/avrdude.exe"
echo $AVRDUDE

#C:\Users\Eric\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino14\etc\avrdude.conf

CONF="C:\Users\Eric\.platformio\packages\tool-avrdude\avrdude.conf"

#CONF="C:\Users\Eric\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino14\etc\avrdude.conf"

# $AVRDUDE -p ? -C $CONF
# $AVRDUDE -c ? -C $CONF

echo $CONF

if [ $usbtiny -eq 1 ]
then
 $AVRDUDE \
  -v \
  -p atmega2560 \
  -c usbtiny \
  -P usb \
  -C $CONF \
  -U flash:w:$TARGET
 echo "test"
fi

if [ $serial -eq 1 ]
then
 ls -l $CONF
   $AVRDUDE \
       -D -v \
       -p atmega2560 \
       -C $CONF \
       -c wiring \
       -b 115200 \
       -P $port \
       -U flash:w:$TARGET
/cygdrive/c/Program\ Files/PuTTY/putty.exe -load ${port}-19200
fi

if [ $avrisp -eq 1 ]
then
   $AVRDUDE \
       -D -v \
       -p atmega2560 \
       -C $CONF
       -c avrisp \
       -b 19200 \
       -P COM4 \
       -U flash:w:$TARGET
fi
