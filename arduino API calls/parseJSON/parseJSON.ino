// EXAMPLE WRITTEN FOR ESP32 NANO
// necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

char ssid[] = "Network";        // your network SSID (name)
char pass[] = "Pass";  // your network password

HTTPClient client; // client class

unsigned long previousMillis = 0;  // will store last time client req was updated
const long interval = 60000;       // interval at which to make a req (milliseconds)

void setup() {
  Serial.begin(115200); // start serial
  while (!Serial) { ; }; // wait until a serial connectio is made

  // configure onboard LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  // wait to get on
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  // print local IP address
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // start the client with the URL we're going to call
  client.begin("http://api.open-notify.org/astros.json");  
  // make the request
  makeRequest();
}

void loop() {
  // only call it every minute
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the time you made the req
    previousMillis = currentMillis;
    // make the request!
    makeRequest();
  }
}

// function that makes the request
void makeRequest() {
  Serial.println("client GET...");
  // start connection and send HTTP header
  int httpCode = client.GET();

  // httpCode will be negative on error. If it's ok, proceed
  if (httpCode > 0) {
    // We know the HTTP header has been sent and the server response has been received
    Serial.print("HTTP GET... code:");
    Serial.println(httpCode);

    // if the requested file is found at the server
    if (httpCode == HTTP_CODE_OK) {
      // store the body as a string 
      String payload = client.getString();
      // parse the data as JSON (see below)
      parseJSON(payload);
    }
  } else { // if we have a problem, report it
    Serial.print("HTTP GET... failed, error: ");
    Serial.println(client.errorToString(httpCode).c_str());
  }
  // close the connection
  client.end();
}

// fxn that parses the data
// receives String as an argument
void parseJSON(String response) {
  // create a new variabkle as a JSON datatype with the info from the server 
  JSONVar JSONresp = JSON.parse(response);
  // print it out serially
  Serial.println(JSONresp);

  // print the keys
  Serial.print("keys: ");
  Serial.println(JSONresp.keys());

  /*
    ******** 
    this JSON has the following structure :
    people : [craft : String, name : String]
    number : int
    message : String
    ******** 
  */

  // get the type of the key "message"
  Serial.println(JSON.typeof(JSONresp["message"]));

  // no need to cast strings to print it out
  String s = JSONresp["message"];
  Serial.print("message: ");
  Serial.println(s);

  // get the total number of ppl in space
  int num = int(JSONresp["number"]); // need to cast the data to an int
  Serial.print("number in space: ");
  Serial.println(num);

  // parse the array inside of the "people" key
  // create a new JSON varaiable
  JSONVar people;
  // store the values in the var
  people = JSONresp["people"];
  // get the length of the array
  int peopleLength = people.length();

  // check the first value in the array
  Serial.println(people[0]);

  // using the length of the array, access every bit of info in there
  for (int x = 0; x < peopleLength; x++) {
    Serial.print("value in array at index ");
    Serial.print(x);
    Serial.print(": ");
    Serial.println(people[x]);
  }

  // get just the names
  for (int x = 0; x < peopleLength; x++) {
    JSONVar name;
    name = people[x]["name"];
    Serial.println(name);
  }

  // blink the on-board LED once for each astronaut
  for(int x =0; x<peopleLength; x++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}
