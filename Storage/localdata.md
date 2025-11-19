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

Most SD cards work with no setup, but it's possible you have one that was used in a computer or camera and it cannot be read by the SD library. Formatting the card will create a file system that the Arduino can read and write to. You can [download a formatting tool](https://www.sdcard.org/downloads/formatter/) from the SD card association, or use your computer's built in disk formatting utility to format the card as with a MS-DOS(FAT) structure.

Note that files and directories need to follow a naming system known as 8.3. That is, the file name is an all caps string  of 8 or fewer characters, and the extension is  is a 3 character extension, for example MYFILE.TXT is valid, while MYSUPERCOOLSTORAGEFINAL.TXT is not.

SD cards generally use **SPI** as way to connect to the Arduino and communicate, by following the standard SPI wiring convention: GND to ground, 5V to 5V, CLK to pin 13, DO to pin 12, DI to pin 11, and CS to pin 10. Some breakout boards might be for 3V microcontrollers ONLY, so make sure to double check.

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

<div align="center"><img src="https://github.com/IDMNYU/DM-GY-9103-L-Sensory-Ecology/blob/49e7934aed0a23a50901faf926b11a1fee7362f0/images/ESP_MicroSDCard_bb.png" alt="Small SD card breakout board" width="50%" /></div>
<div align="center"><sub>Arduino Nano ESP32 + Adafruit MicroSD card breakout board.</sub></div><br>

```
/* This is a SD card tester code that reads the size of the data stored on the card and reads some of the files on the card if named correctly
*/

#include "FS.h"
#include "SD.h"
#include "SPI.h"

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}

void setup(){
    Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    listDir(SD, "/", 0);
    createDir(SD, "/mydir");
    listDir(SD, "/", 0);
    removeDir(SD, "/mydir");
    listDir(SD, "/", 2);
    writeFile(SD, "/hello.txt", "Hello ");
    appendFile(SD, "/hello.txt", "World!\n");
    readFile(SD, "/hello.txt");
    deleteFile(SD, "/foo.txt");
    renameFile(SD, "/hello.txt", "/foo.txt");
    readFile(SD, "/foo.txt");
    testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void loop(){

}
```

There's a great [example in the Arduino documentation on using an SD card as a datalogger](https://docs.arduino.cc/learn/programming/sd-guide/) [(Archive.org version of the tutorial page)](https://web.archive.org/web/20201112012317/https://www.arduino.cc/en/Tutorial/LibraryExamples/Datalogger). 

There are a number of different SD libraries out there, check if your board is compatible with the [default Arduino version](https://docs.arduino.cc/libraries/sd/), or if you need to use an alternate one. 

## SPIFFS and LittleFS on ESP32 boards

The ESP32 microprocessors contain flash memory that can hold a filesystem, including full websites — images, css, javascript, html, and other text files. This is an advanced storage mechanism that can be quirky at best, particularly when using the regular Arduino IDE. Go after these if you're looking to have a full fledged website stored on an ESP32, or expected to store massive amounts of files in flash memory. 

The Arduino Nano ESP32 boards have a total of 8Megs of RAM that can be used for this purpose

### SPIFFS
SPIFFS is an acronym for Serial Peripheral Interface Flash File System. It is designed to be a lightweight system to interface between microcontrollers and flash memory devices. Before accessing the storage on the flash module, you will need to set up the board as indicated on [this tutorial page](https://docs.arduino.cc/tutorials/nano-esp32/spiff/). 

Once you have initialized the board per the instructions above, [follow the instructions at the bottom of this page for loading a SPIFFS file uploader plugin to the Arduino IDE](https://github.com/espx-cz/arduino-spiffs-upload#installation). 

SPIFFS creates a flat file structure, there are no folders — everything lives at the root of the directory. 


### LittleFS
LittleFS is a slightly more modern file system than SPIFFS, but largely has the same functionality. You can create, delete, write, and modify html, css, javascript and other text files. You can save images to the flash as well. That said, it is slightly *more* complex than SPIFFS to use.

It supports nested folders and has a more robust recovery system in case of failure during a power outage than SPIFFS.

This [forum post walks you through the process of setting up a board](https://forum.arduino.cc/t/best-method-for-utilizing-on-board-flash/1222469/15) for use with LittleFS. There is an [upload tool you can add to the Arduino IDE here](https://github.com/earlephilhower/arduino-littlefs-upload), installation instructions are at the bottom of the page.


