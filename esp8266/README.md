Instructions:

ucontroller ESP8266 D1 Mini

Install Arduino IDE/additional boards etc
https://diyi0t.com/esp8266-wemos-d1-mini-tutorial/

OR

Via VSCODE platformio extension


Probems: Platformio can't find Python 3.10 despite installed. FIX -> sudo apt-get install python3-venv

Problem:Upload speed in VScode. FIX -> ?



Problem 1: Port greyed in Arduino IDE
FIX: Stop braille daemons brltty

systemctl stop brltty-udev.service
sudo systemctl mask brltty-udev.service
systemctl stop brltty.service
systemctl disable brltty.service



Problem 2: Access to /dev/ttyUSB0 denied
FIX (temporary): Give access 

sudo chmod a+rw /dev/ttyUSB0

