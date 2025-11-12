# Exploring Local Storage for Arduino Projects

When working with Arduino projects that collect or process data, it’s often useful to store information locally rather than sending it to and/or receiving it from the cloud. 

Arduino boards support two really useful types of local storage: **EEPROM**, which is a small built-in memory ideal for saving settings, storing  values, or other small bits of data that you want to be able to retrieve even when the board is powered off; and **SD cards**, which provide much larger, removable storage for logging larger data sets like sensor data, updating and retrieving measurements, or saving full on files like text files, images and audio.

## EEPROM

The microcontroller on most Arduino boards includes usually about **512 bytes** of EEPROM, a type of non-volatile memory that retains its values even when the board is powered off, just like a very tiny built-in hard drive. 

**EEPROM** (Electrically Erasable Programmable Read-Only Memory, or E²PROM) is used to store really small pieces of data that must persist between power on/off sessions, such as configuration/start-up settings, etc. 

The [EEPROM library](https://docs.arduino.cc/learn/programming/eeprom-guide/) is included by default with the Arduino platform, so no external installation is required.
