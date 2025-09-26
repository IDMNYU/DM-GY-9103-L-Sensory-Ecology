#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

char ssid[] = "NETWORK";         // your network SSID (name)
char pass[] = "PASS";  // your network password

String serverName = "http://colormind.io/api/";

HTTPClient client;

unsigned long previousMillis = 0;  // will store last time client req was updated
const long interval = 360000;      // interval at which to make a req (milliseconds)

int rv = 0;
int gv = 0;
int bv = 0;

int rpin = 4;
int gpin = 5;
int bpin = 6;

int switchPin = 3;
int pVal = 1;

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; };
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // log on to network
  WiFi.begin(ssid, pass);

  // wait to get on
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  // print put local IP address and verify port
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // make the request
  makeRequest();
}

void makeRequest() {
  Serial.println("making a cnxn");
  // Your Domain name with URL path or IP address with path
  client.begin(serverName);
  // Specify content-type header
  client.addHeader("Content-Type", "application/json");
  // Data to send with HTTP POST
  String httpRequestData = "{\"model\":\"default\"}";
  // Send HTTP POST request
  int httpCode = client.POST(httpRequestData);

  Serial.print("HTTP Response code: ");
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    // parse the data
    String payload = client.getString();
    parseJSON(payload);
  } else {  // if we have a problem, report it
    Serial.print("HTTP POST... failed, error: ");
    Serial.println(client.errorToString(httpCode).c_str());
  }
  // Free resources
  client.end();
}

void loop() {
  analogWrite(rpin, rv);
  analogWrite(gpin, gv);
  analogWrite(bpin, bv);
  int val = digitalRead(switchPin);
  if (pVal != val && val == LOW) {
    rv = 0;
    gv = 0;
    bv = 0;
    analogWrite(rpin, rv);
    analogWrite(gpin, gv);
    analogWrite(bpin, bv);
    makeRequest();
  }
  pVal = val;
  delay(10);
}

void parseJSON(String response) {
  // create a new JSON datatype with the info from the server
  JSONVar JSONresp = JSON.parse(response);

  // print it out!
  Serial.println(JSONresp["result"][0]);
  rv = JSONresp["result"][0][0];
  gv = JSONresp["result"][0][1];
  bv = JSONresp["result"][0][2];
  /*
  Serial.println(JSONresp["result"][1]);
  Serial.println(JSONresp["result"][2]);
  Serial.println(JSONresp["result"][3]);
  Serial.println(JSONresp["result"][4]);
  */
  Serial.print(rv);
  Serial.print(",");
  Serial.print(gv);
  Serial.print(",");
  Serial.println(bv);
}