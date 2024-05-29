# Raspberry-Pi---SenseHat---I2C-SPI
The goal of this project is to get familiar with I²C and SPI protocols in C language. Hence we will communicate with the LP25H sensor of SenseHat (slave) from Raspberry Pi 3 (master) and get the temperature and pressure value from the sensor.

# **STEP1**:

Check if these protocols are enabled on the Raspberry Pi(RPi), and if not enable them:

`$lsmod | grep -e spi -e i2c` or `$ls /dev/i2c* /dev/spi*`. If nothing comes up they are disabled(was the case).

### Method 1: In terminal `$sudo raspi-config nonint get_i2c`, will return 1 if disabled. To enable, `$sudo raspi-config nonint do_i2c 0`. Same for spi.

### Method 2: Application Menu -> Preferences -> Raspberry configuration -> Interfaces -> Toggle I2C and SPI.

### Method 3: In terminal `$sudo raspi-config` and enable the protocols.

#**STEP2**:

Get addresses of devices and pin numbers(if needed) of RPi using I2C and SPI.

To scan address range: `$sudo i2cdetect -y 1`
Can also use sensehat documentation: https://pinout.xyz/pinout/sense_hat
-> LP25H sensor address is 0x5c on the i2c bus.

Pin numbers either via `$gpio readall`, or documentation of RPi. 

In my case the senseHat plugs in all the RPi pins so no need to check for pins.

#**STEP3**:

Code to get the pressure and temperature values.
