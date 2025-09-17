# DHT11 (Digital temperature & humidity)

The DHT11 is a low-cost combined humidity and temperature sensor. Inside, a polymer capacitive element measures moisture in the air and a thermistor measures temperature. A small IC converts those readings to a digital signal on a single DATA line (a timing-based, one-wire-style protocol). It’s simple, cheap, and fine for basic indoor projects as long as you don’t expect accuracy nor speed.

## Typical specs (DHT11)

**Humidity range:** ~20–90% RH, accuracy ±5% RH, resolution 1%

**Temperature range:** ~0–50 °C, accuracy ±2 °C, resolution 1 °C

**Sampling rate:** up to 1 reading/second (don’t poll faster)

**Supply:** 3.3–5 V (use 3.3 V with the Nano ESP32)

**Interface:** single DATA pin with pull-up resistor (often built-in on 3-pin modules)

**Wiring (3-pin module → Arduino Nano ESP32):**

VCC → 3V3

GND → GND

DATA → D2 (any GPIO works).

If you have a bare 4-pin DHT11, add a 10 kΩ pull-up from DATA to VCC.


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
## **Tips**

Read no faster than once per second; 2 s is even safer for reliability.

Keep wires short (the protocol is timing-sensitive).

Let it stabilize 1–2 minutes after power-up for best readings.

Keep the sensor away from heat sources to avoid inflated temps.

Need better accuracy or wider range? Use a DHT22/AM2302 or a modern I²C sensor (SHT4x, AHTx, BME280).
