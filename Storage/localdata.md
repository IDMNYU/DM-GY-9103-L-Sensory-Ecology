# Exploring Local Storage for Arduino Projects

When working with Arduino projects that collect or process data, it’s often useful to store information locally rather than sending it to and/or receiving it from the cloud. 

Arduino boards support two really useful types of local storage: **EEPROM**, which is a small built-in memory ideal for saving settings, storing values, or other small bits of data that you want to be able to retrieve even when the board is powered off; and **SD cards**, which provide much larger, removable storage for logging larger data sets like sensor data, updating and retrieving measurements, or saving full on files like text files, images and audio.

## EEPROM

The microcontroller on most Arduino boards includes usually about **512 bytes** of EEPROM, a type of non-volatile memory that retains its values even when the board is powered off, just like a very tiny built-in hard drive. 

**EEPROM** (Electrically Erasable Programmable Read-Only Memory, or E²PROM) is used to store really small pieces of data that must persist between power on/off sessions, such as configuration/start-up settings, etc. 

The [EEPROM library](https://docs.arduino.cc/learn/programming/eeprom-guide/) is included by default with the Arduino platform, so no external installation is required.

Here is an example of how to save sensor readings onto a EEPROM on an Arduino Nano ESP 32

```
/*
   EEPROM Write

   Stores sensor values into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.
*/

#include "EEPROM.h"

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
// starting with 0

int addr = 0;

#define EEPROM_SIZE 64
// Defines the number of bytes to allocate for EEPROM (max 512).

void setup(){

  Serial.begin(115200);
  Serial.println("start...");

  if (!EEPROM.begin(EEPROM_SIZE)){
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  Serial.println(" bytes read from Flash . Values are:");

  for (int i = 0; i < EEPROM_SIZE; i++){
    Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
  }
  Serial.println();
  Serial.println("writing random n. in memory");
}

void loop(){

  // it is good practice to divide analog readings by 4 to take less space in the EEPROM

  int val = analogRead(2) / 4;
  
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.

  EEPROM.write(addr, val);
  Serial.print(val); Serial.print(" ");

  // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 0 when we hit 512.
  // save all changes to the flash.
  addr = addr + 1;
  if (addr == EEPROM_SIZE){
    Serial.println();
    addr = 0;
    EEPROM.commit();
    Serial.print(EEPROM_SIZE);
    Serial.println(" bytes written on Flash . Values are:");
    for (int i = 0; i < EEPROM_SIZE; i++)
    {
      Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
    }
    Serial.println(); Serial.println("----------------------------------");
  }

  delay(100);
}

```

## MicroSD Card Breakout Boards

**MicroSD card breakout boards** make it easy to add removable, high-capacity storage to Arduino and other embedded microcontroller projects. They typically include a card slot, voltage regulation, and level shifting to safely interface 3.3 V SD cards with 5 V microcontrollers, enabling convenient data logging, file storage, and media playback.

<div align="center"><img src="https://cdn-shop.adafruit.com/970x728/254-02.jpg" alt="Small SD card breakout board" width="60%" /></div>
<div align="center"><sub>Adafruit MicroSD card breakout board.</sub></div><br>

There are a few microSD card breakout boards out there, or some boards meant specifically for datalogging purposes come with microSD card holders already built in.  

They generally use **SPI** as way to connect to the Arduino and communicate, by following the standard SPI wiring convention: GND to ground, 5V to 5V, CLK to pin 13, DO to pin 12, DI to pin 11, and CS to pin 10. Some breakout boards might be for 3V microcontrollers ONLY, so make sure to double check.

```
/*
 * Connect the SD card to the following pins:
 *
 * SD Card | Nano ESP32
 *
 *    CS       10 
 *    D1       11
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK - 13
 *    D0       12
 */
```
You can then use the Arduino IDE's native SD library which supports FAT and FAT32 SD cards. 

<div align="center"><img src="https://cdn-shop.adafruit.com/970x728/254-02.jpg" alt="Small SD card breakout board" width="60%" /></div>
<div align="center"><sub>Adafruit MicroSD card breakout board.</sub></div><br>



