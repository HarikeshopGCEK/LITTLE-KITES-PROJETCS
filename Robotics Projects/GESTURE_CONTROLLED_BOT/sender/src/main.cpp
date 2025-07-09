#include <Wire.h>
#include <MPU6050.h>
#include <esp_now.h>
#include <WiFi.h>

MPU6050 mpu;
int16_t ax, ay, az;

uint8_t receiverAddress[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF}; // Replace with NodeMCU's MAC

typedef struct struct_message {
  char gesture[10];
} struct_message;

struct_message gestureData;

void sendGesture(const char* gesture) {
  strcpy(gestureData.gesture, gesture);
  esp_now_send(receiverAddress, (uint8_t*)&gestureData, sizeof(gestureData));
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  if (ay > 10000) sendGesture("forward");
  else if (ay < -10000) sendGesture("backward");
  else if (ax > 10000) sendGesture("right");
  else if (ax < -10000) sendGesture("left");
  else sendGesture("stop");

  delay(200); // smooth output
}
