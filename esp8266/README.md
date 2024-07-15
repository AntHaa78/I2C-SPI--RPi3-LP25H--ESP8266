Instructions:

ucontroller ESP8266 D1 Mini

Install Arduino IDE/additional boards etc
https://diyi0t.com/esp8266-wemos-d1-mini-tutorial/

OR

Via VSCODE platformio extension

Problem 1: Port greyed in Arduino IDE
Solution: Stop braille daemons brltty

systemctl stop brltty-udev.service
sudo systemctl mask brltty-udev.service
systemctl stop brltty.service
systemctl disable brltty.service



Problem 2: Access to /dev/ttyUSB0 denied
Solution (temporary): Give access 

sudo chmod a+rw /dev/ttyUSB0

