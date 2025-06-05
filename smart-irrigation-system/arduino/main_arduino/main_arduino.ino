#include <WiFiS3.h>
WiFiServer server(80);
const int relayPins[4] = {2, 3, 4, 8};
const int pumpRelay = 9;
const int pumpLED = 6;
const int wifiLED = 5;
const int switchPin = 7;

void setup() {
  for (int i = 0; i < 4; i++) pinMode(relayPins[i], OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(pumpLED, OUTPUT);
  pinMode(wifiLED, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  WiFi.begin("YOUR_SSID", "YOUR_PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  digitalWrite(wifiLED, HIGH);
  server.begin();
}

void loop() {
  if (digitalRead(switchPin) == LOW) manualIrrigate();
  WiFiClient client = server.available();
  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();
    if (req.indexOf("/manualon") != -1) manualIrrigate();
    else if (req.indexOf("/status") != -1) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json\n");
      client.println("{\"s1\":3200,\"s2\":3100,\"s3\":2900,\"s4\":3000,\"pump\":false,\"wifi\":true}");
    }
    else {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html\n");
      client.println("Smart Orchard");
    }
    client.stop();
  }
}

void manualIrrigate() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pumpRelay, HIGH);
    digitalWrite(pumpLED, HIGH);
    digitalWrite(relayPins[i], HIGH);
    delay(120000);
    digitalWrite(relayPins[i], LOW);
    digitalWrite(pumpRelay, LOW);
    digitalWrite(pumpLED, LOW);
  }
}