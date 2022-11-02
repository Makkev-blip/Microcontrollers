#/bin/bash

#set baudrate for MySmartUSB: 19200
stty ospeed 19200 -F COM3

#send command to set to UART mode
echo -en '\xE6' > COM3
echo -en '\xB5' > COM3
echo -en '\xBA' > COM3
echo -en '\xB9' > COM3
echo -en '\xB2' > COM3
echo -en '\xB3' > COM3
echo -en '\xA9' > COM3
echo -en '\x70' > COM3
