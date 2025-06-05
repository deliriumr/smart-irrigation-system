#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Replace with your Firebase Realtime DB URL (without https:// and no trailing slash)
const char* firebaseHost = "your-project-id.firebaseio.com";
const int firebasePort = 443; // HTTPS
const char* firebaseAuth = "YOUR_FIREBASE_DATABASE_SECRET_OR_TOKEN";

// Firebase paths
const char* path = "/orchard/status.json";

// Sensor pins
const int sensorPins[4] = {A0, A1, A2, A3};

WiFiSSLClient wifiClient;
HttpClient client = HttpClient(wifiClient, firebaseHost, firebasePort);

void setup() {
  Serial.begin(9600);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  // Read sensors
  int moisture[4];
  for (int i = 0; i < 4; i++) {
    moisture[i] = analogRead(sensorPins[i]);
    delay(50);
  }

  // Format as JSON
  String json = "{";
  json += "\"zone1\":" + String(moisture[0]) + ",";
  json += "\"zone2\":" + String(moisture[1]) + ",";
  json += "\"zone3\":" + String(moisture[2]) + ",";
  json += "\"zone4\":" + String(moisture[3]);
  json += "}";

  // Send to Firebase
  client.beginRequest();
  client.put(path);
  client.sendHeader("Host", firebaseHost);
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", json.le
