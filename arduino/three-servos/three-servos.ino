#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Servo.h>

ESP8266WiFiMulti WiFiMulti;
Servo servoA;
Servo servoB;
Servo servoC;

// Pins to which your Servo is connected
int PIN_D5 = 14; // ESP pin 14 = Arduino pin D5
int PIN_D6 = 12; // ESP pin 12 = Arduino pin D6
int PIN_D7 = 13; // ESP pin 13 = Arduino pin D7

// Your Sobots token (see sobots.xyz)
String TOKEN = "";

// Your Wifi Credentials
char WIFI_NAME[30] = "";
char WIFI_PASS[30] = "";

// Seconds between receive checking
int INTERVAL = 10;

//
// Function which causes action when message received
//

void act(double x, double y, double z) {
    Serial.println(x * 180);
    Serial.println(y * 180);
    Serial.println(z * 180);
    servoA.write(x * 180);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    servoB.write(y * 180);              
    delay(15);                      
    servoC.write(z * 180);              
    delay(15);   
}

//
// Function called when device is powered on
//

void setup() {
  // Setup serial port for debugging
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  // Wait for everything to initialise
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  //Setup servos
  servoA.attach(PIN_D5);
  servoB.attach(PIN_D6);
  servoC.attach(PIN_D7);
  
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_NAME, WIFI_PASS);
}


//
// Function to fetch new messages
//

String receive() {
  WiFiClient client;
  HTTPClient http;
  
  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://us-central1-sobots.cloudfunctions.net/list/?limit=1&token="+TOKEN)) {
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

        // Allow response to load
        delay(5000);
         
        String payload = http.getString();
        Serial.println("Payload");
        Serial.println(payload);

        StaticJsonDocument<500> doc;

        DeserializationError jsonError = deserializeJson(doc, payload);
        if (jsonError) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(jsonError.c_str());
        } else {
          processMessage(doc);
        }
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  }
  http.end();
  return "HELLO";
}

//
// Function to process received messages
//

void processMessage(StaticJsonDocument<500> doc) {
    bool success = doc["success"];
    Serial.print(F("API Says it was a success? "));
    Serial.println(success);
    JsonObject messages_0 = doc["messages"][0];
    long messages_0_date = messages_0["date"];
    const char* messages_0_recipient = messages_0["recipient"];
    const char* messages_0_recipientName = messages_0["recipientName"];
    const char* messages_0_sender = messages_0["sender"];
    const char* messages_0_senderName = messages_0["senderName"];
    double x = messages_0["x"]; // 1
    double y = messages_0["y"]; // 1
    double z = messages_0["z"]; // 1
    // preform action
    act(x,y,z);
}

//
// Function is executed in a loop i.e. once setup this function runs repeatedly
//

void loop() {
  
  // Make sure WiFi connected
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    // Look for new messages
    receive();
  } else {
    // Report no wifi
    Serial.printf("Wifi not connect, will try again shortly\n");
  }
  // Wait X seconds before running again
  delay(INTERVAL * 1000);
}
