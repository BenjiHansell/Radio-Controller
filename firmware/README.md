# Firmware

The firmware is written in C++ using Platformio and the Arduino framework.  The code is object oriented with minimal use of the STL (as it runs on a microcontroller).

## Libraries

The following libraries are needed for the code to compile:

Library | Purpose | URL
------- | ------- | ---
StandardCplusplus | An STL port for Arduino | https://github.com/maniacbug/StandardCplusplus
RF24 | A driver for the NRF24L01+ radio module | https://github.com/nRF24/RF24
static_queue | My own implementation of std::queue for embedded systems | https://github.com/BenjiHansell/static_queue
NewliquidCrystal | A driver for the LCD | https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
Adafruit_Neopixel | A driver for the LEDs | https://github.com/adafruit/Adafruit_NeoPixel

## Data Sources

The user interface is designed around inheritance from two base classes:
Any class which inherits from DataSource can provide data for the LCD in the form of a string.  Any class which inherits from LcdDataSource can be associated with an LED and provide data in the form of a colour.
