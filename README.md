# IT8951-ePaper
## waveshare electronics
![waveshare_logo.png](waveshare_logo.png)
http://www.waveshare.net  
https://www.waveshare.com  

## 中文 ## 
e-Paper IT8951 Driver HAT通用驱动代码，适用于IT8951驱动的并口墨水屏，支持树莓派和STM32

## English ## 
e-Paper IT8951 Driver HAT universal Driver code, suitable for IT8951 Driver parallel ink screen, support Raspberry Pi and STM32

## BCM2835 library installation ##
BCM2835 need to be installed on the device. Follow the procedure bwelow for installation:

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz

tar zxvf bcm2835-1.68.tar.gz

cd bcm2835-1.68

./configure

make

sudo make check

sudo make install

## Hardware:

PCF8574 Remote 8-bit I/O I2C expander
Hitachi HD44780 2x16 5x7 LCD display
Raspberry Pi 3 Model B+

## Installation ##

git clone https://github.com/lciscon/IT8951-ePaper.git

cd IT8951-ePaper/RasMult

make
