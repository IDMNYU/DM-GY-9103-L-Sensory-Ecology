# Arduino Nano ESP32 & DHT11 Humidity and Temperature Sensor 

Some text about the sensor 

```

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define DHTPIN  D4       // Data pin from the DHT11 (use 2 if you prefer plain GPIO numbers)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int sensorValue = 0;  // value read from the pot
int analogInPin = A2;
//int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  sensorValue = analogRead(analogInPin);

  float h = dht.readHumidity();
  float t = dht.readTemperature();      // Celsius
  float f = dht.readTemperature(true);  // Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT11 (check wiring/power)"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(h, 1);
    Serial.print(F("%  Temp: "));
    Serial.print(t, 1);
    Serial.print(F("°C  "));
    Serial.print(f, 1);
    Serial.println(F("°F"));
    Serial.print(F("Moisture: "));
    Serial.println(sensorValue);
  }

  delay(500); // 1 second between reads
}
```
