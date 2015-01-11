STM32F4-Discovery-example-code
==============================

This is my example code for the STM32F4 Discovers using the RTOS ChibiOS.

requirements
------------
* Chibios 2.5.0+ (or a recent development snapshot)
* arm toolchain (e.g. arm-none-eabi from summon-arm)

features
--------
* serial over USB console
* several background blinker thread
* code structured into separate files

usage
-----
* edit the Makefile and point "CHIBIOS = ../../chibios" to your ChibiOS folder
* make
* connect the STM32F4 Discovery with both USB connectors
* flash the STM32F4: st-flash write build/ch.bin 0x8000000
* use your favorite terminal programm to connect to the Serial Port (/dev/ttyACM0 for me, probably COM1 on Windows)

console commands
----------------
* help
* exit
* info
* systime
* mem
* threads
* blinkspeed #speed (changes blinker period to #speed ms, short: bs)

