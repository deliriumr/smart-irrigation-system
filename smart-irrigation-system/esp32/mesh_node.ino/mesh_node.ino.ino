#include <WiFi.h>
#include <esp_now.h>

typedef struct struct_message {
  int node_id;
  int moisture;
  bool valve_state;
} struct_message;

struct_message dataOut;
struct_message dataIn;

uint8_t baseMac[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF};  // Replace with MAC of your bridge ESP32

#define MOISTURE_PIN A0
#define RELAY_PIN 4
#define NODE_ID 1  // Change this for each node

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&dataIn, incomingData, sizeof(dataIn));
  if (dataIn.node_id == NODE_ID) {
    digitalWrite(RELAY_PIN, dataIn.valve_state ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onDataRecv);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, baseMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  dataOut.node_id = NODE_ID;
  dataOut.moisture = analogRead(MOISTURE_PIN);
  dataOut.valve_state = digitalRead(RELAY_PIN);
  esp_now_send(baseMac, (uint8_t*)&dataOut, sizeof(dataOut));
  delay(30000); // send every 30s
}
