# PCB

The PCB is designed using KiCAD.  The schematic is based around that of the Arduino Pro Mini, with an ATmega328P clocked at 16 MHz on a 5V supply.  There are pin headers for connecting an SPI NRF24L01+ radio module (which has a dedicated 3.3V supply), an I2C LCD display, some LEDs, switches, analog sticks and a UART programmer.  There is also a potential divider for reading the battery voltage.

## Order boards

I ordered my boards at OSH Park https://oshpark.com/shared_projects/BLpBqENQ

## Room for improvement

This PCB is the first iteration, with a few imperfections.  If I order more copies I will make the following minor modifications:
* A rectangular (rather than square) form factor would allow for more comfortable vertical mounting inside the radio controller
* The rotary encoder needs its own header with power, ground and 3 digital inputs
* PD0, PD1 and PD2 could be broken out for use with additional aux switches

## Long term improvements

The following major features could also be added later:
* A more powerful (yet inexpensive) MCU, such as the STM32F103C8T6
* 1S Li-Ion recharge and boost circuitry (via a USB-B or USB-C port)
* On-board programming (via the same USB port)
