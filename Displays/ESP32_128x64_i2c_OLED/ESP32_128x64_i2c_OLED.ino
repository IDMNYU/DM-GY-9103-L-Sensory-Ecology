#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// on esp32 nano it's SCL on A5 and sda on a4
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorPin = A0;
int sensorVal = 0;


void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    /// wait to init
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.


  // Clear the buffer
  display.clearDisplay();

  // draw a rectangle
  display.drawRect(0, 0, 128, 16, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.setCursor(4, 4);
  display.setTextColor(WHITE, BLACK);
  display.print("Hello class");
  display.display();
  delay(5000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

}

void loop() {
  // read the value of the sensor
  sensorVal = analogRead(sensorPin);

  // print it out to the screen!
  display.drawRect(0, 0, 128, 16, SSD1306_WHITE);
  display.setCursor(4, 4);
  display.setTextColor(WHITE, BLACK);
  display.print("Sensor Reading");

  display.setCursor(4, 20);
  display.setTextSize(2);
  display.print("Value : ");
  display.print(sensorVal);
  display.display();
  delay(16);
}

