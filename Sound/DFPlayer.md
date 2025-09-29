# Playing audio files with the DFRobot Mini mp3 Player


The [DFPlayer Mini MP3 Player](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299) For Arduino is a small and low cost MP3 module with an simplified output directly to the speaker. The module can be used as a stand alone module with attached battery, speaker and push buttons or used in combination with microcontrollers such as Arduino, ESP32, Raspberry Pi and others.

All the technical specifications and details of this little board are on the DFRobot website, and you can purchase it on different platforms including the [DFRobot store website](https://www.dfrobot.com/product-1121.html). 

# Some Tech Specifications

- Sampling rates (kHz): 8/11.025/12/16/22.05/24/32/44.1/48
- 24 -bit DAC output, support for dynamic range 90dB , SNR support 85dB
- Takes a SD Card! Fully supports FAT16 , FAT32 file system, maximum support 32GB
- Offers a variety of control modes (I/O control mode, serial mode, AD button control mode)
- Audio data sorted by folder, supports up to 100 folders, every folder can hold up to 255 songs
- 30 level adjustable volume, 6 -level EQ adjustable
- Working voltage: DC3.2~5V

# Arduino Nano ESP32 and DFPlayer Mini Wiring 

```
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include <HardwareSerial.h>

HardwareSerial FPSerial(1);           // use UART1
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);
  delay(300);

  // Your wiring: DF TX -> D6 (ESP RX), DF RX -> D7 (ESP TX)
  FPSerial.begin(9600, SERIAL_8N1, /*rx=*/D6, /*tx=*/D7);
  delay(500); // give DFPlayer time to boot

  Serial.println("\nInit DFPlayer…");
  if (!myDFPlayer.begin(FPSerial, /*isACK=*/false, /*doReset=*/true)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1) Check wiring (DF TX->D6, DF RX->D7, GND common)"));
    Serial.println(F("2) FAT32 SD with files like 0001.mp3 in root or /mp3"));
    while (true) delay(10);
  }

  Serial.println(F("DFPlayer online."));
  myDFPlayer.volume(20);   // 0..30
  //myDFPlayer.play(1);      // plays 0001.mp3
  //myDFPlayer.playMp3Folder(1);
  //myDFPlayer.enableLoopAll(); //loop all mp3 files.

}

void loop()
{
  static unsigned long timer = millis();
  
  if (millis() - timer > 60000) {
    timer = millis();
    //myDFPlayer.next();  //Play next mp3 every 3 second?
    myDFPlayer.playMp3Folder(1);
  }
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
