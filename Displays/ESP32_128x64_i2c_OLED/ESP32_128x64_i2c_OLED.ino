#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// on esp32 nano it's SCL on A5 and SDA on a4
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorPin = A0;
int sensorVal = 0;


void setup() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    /// wait to init
  }

  // Clear the display buffer
  display.clearDisplay();

  // draw a rectangle
  display.drawRect(0, 0, 128, 16, SSD1306_WHITE);
  // move the cursor
  display.setCursor(4, 4);
  // set the text color
  display.setTextColor(WHITE, BLACK);
  // write some text
    display.print("Hello class");
  // update the display
  display.display();
  delay(1000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display().

  // some static text
  display.drawRect(0, 0, 128, 16, SSD1306_WHITE);
  display.setCursor(4, 4);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.print("Sensor Reading");
  display.setCursor(4, 20);
  display.setTextSize(2);
  display.print("Value:");
}

void loop() {
  // read the value of the sensor
  sensorVal = analogRead(sensorPin);

  // move the cursor to the location
  display.setCursor(75, 20);
  // erase what was there previously
  display.print("    ");
  // move the cursor back to position
  display.setCursor(75, 20);
  // print the sensor value
  display.print(sensorVal);

  // down here you could display a graph of the last 128 sensor readings

  display.display(); // update the display
  // slight delay - 16ms == 60fps
  delay(16);
}
