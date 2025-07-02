#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LSPEED 255
#define RSPEED 255
#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5
#define ENA 10
#define ENB 11

ESP8266WebServer server(80);
const char* ssid = "your_ssid"; // Replace with your WiFi SSID
const char* password = "your_password"; // Replace with your WiFi password
void forward() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void backward() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void left() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void right() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void stop() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void handleRoot() {
    String html = "<html><body>";
    html += "<h1>Web Controlled Car</h1>";
    html += "<button onclick=\"location.href='/forward'\">Forward</button>";
    html += "<button onclick=\"location.href='/backward'\">Backward</button>";
    html += "<button onclick=\"location.href='/left'\">Left</button>";
    html += "<button onclick=\"location.href='/right'\">Right</button>";
    html += "<button onclick=\"location.href='/stop'\">Stop</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}
void setup() {
    Serial.begin(115200);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    server.on("/", handleRoot);
    server.on("/forward", forward);
    server.on("/backward", backward);
    server.on("/left", left);
    server.on("/right", right);
    server.on("/stop", stop);

    server.begin();
}
void loop() {
    server.handleClient();
    // You can add additional logic here if needed
    // For example, you can read sensors or handle other tasks
}