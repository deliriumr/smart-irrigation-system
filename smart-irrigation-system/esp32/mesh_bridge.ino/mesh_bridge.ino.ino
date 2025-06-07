#include <WiFi.h>
#include <esp_now.h>

typedef struct struct_message {
  int node_id;
  int moisture;
  bool valve_state;
} struct_message;

struct_message incomingData;

void onDataRecv(const uint8_t * mac, const uint8_t *incomingDataRaw, int len) {
  memcpy(&incomingData, incomingDataRaw, sizeof(incomingData));
  Serial.print("NODE:");
  Serial.print(incomingData.node_id);
  Serial.print(",MOISTURE:");
  Serial.print(incomingData.moisture);
  Serial.print(",VALVE:");
  Serial.println(incomingData.valve_state);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  // Nothing needed here
}
