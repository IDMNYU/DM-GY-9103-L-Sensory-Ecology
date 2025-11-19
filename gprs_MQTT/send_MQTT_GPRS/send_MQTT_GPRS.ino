#include <MKRGSM.h>
#include <ArduinoMqttClient.h>
int ledPin = 13;


const char PINNUMBER[] = "";
// APN data
const char GPRS_APN[] = "YOUR APN HERE";
const char GPRS_LOGIN[] = "";
const char GPRS_PASSWORD[] = "";

GSMClient client;
GPRS gprs;
GSM gsmAccess;

MqttClient mqttClient(client);

unsigned long lastMillis = 0;

const char broker[] = "BROKER NAME HERE";
int port = 1883;
const char topic[] = "TOPIC GOES HERE";

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  while (!Serial) { ; }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to network");
  // connection state
  bool connected = false;

  // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
  while (!connected) {
    if ((gsmAccess.begin(PINNUMBER) == GSM_READY) && (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  mqttClient.setId("reader");

  // You can provide a username and password for authentication
  mqttClient.setUsernamePassword("USERNAME", "PASSWORD");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keepalive messages which
  // avoid the broker from disconnecting
  mqttClient.poll();

  unsigned long cTime = millis();
  //update once a minute
  if (cTime - lastMillis > 60000) {

    int val = analogRead(A0);
    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(val);

    // send message
    mqttClient.beginMessage(topic);
    mqttClient.print(val);
    mqttClient.endMessage();
    lastMillis = cTime;
  }
}