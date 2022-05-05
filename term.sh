#!/bin/bash

if [ -z $1 ]
then
 port="COM9"
else
 port=$1
fi

#echo $port

/cygdrive/c/Program\ Files/PuTTY/putty.exe -load ${port}-19200

