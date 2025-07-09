#include <ESP8266WiFi.h>
#include <espnow.h>

#define LM1 D1
#define LM2 D2
#define RM1 D3
#define RM2 D4

typedef struct struct_message {
  char gesture[10];
} struct_message;

struct_message receivedGesture;

void moveBot(const char* gesture) {
  if (strcmp(gesture, "forward") == 0) {
    digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
  } else if (strcmp(gesture, "backward") == 0) {
    digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH);
  } else if (strcmp(gesture, "left") == 0) {
    digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
  } else if (strcmp(gesture, "right") == 0) {
    digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH);
  } else {
    digitalWrite(LM1, LOW); digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW); digitalWrite(RM2, LOW);
  }
}

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&receivedGesture, incomingData, sizeof(receivedGesture));
  Serial.print("Gesture: ");
  Serial.println(receivedGesture.gesture);
  moveBot(receivedGesture.gesture);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing here; callback handles everything
}
