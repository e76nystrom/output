rem set TARGET=".pioenvs\megaatmega2560\firmware.hex:i"
set TARGET="C:\Users\\.hex:i"

rem set AVRDUDE="c:\Users\Eric\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino14\bin\avrdude.exe"
set AVRDUDE="c:\Program Files (x86)\\avrdude.exe"

rem set CONF="C:\Users\Eric\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino14\etc\avrdude.conf"
set CONF="C:\Program Files (x86)\\avrdude.conf"

%AVRDUDE% -v -p m1284p -c usbtiny -P usb -C %CONF% -U flash:w:%TARGET%

