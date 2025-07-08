#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "your_ssid";         // Replace with your WiFi SSID
const char *password = "your_password"; // Replace with your WiFi password
const char *serverUrl = "http://<your_ip>:5000/led"; // Replace with your server URL
int led = 2; // Replace with your server URL
void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    Serial.println("IP Address: " + WiFi.localIP().toString());
    pinMode(led, OUTPUT);   // Set the LED pin as output
    digitalWrite(led, LOW); // Initialize LED to OFF state
}

void loop()
{
    // Your main code here
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(serverUrl);
        int httpCode = http.GET();
        if (httpCode > 0)
        {
            String payload = http.getString();
            Serial.println("Response: " + payload);
            if (payload == "1")
            {
                Serial.println("LED is ON");
                digitalWrite(led, HIGH); // Turn on the LED
            }
            else if (payload == "0")
            {
                Serial.println("LED is OFF");
                digitalWrite(led, LOW); // Turn off the LED
            }
            else
            {
                Serial.println("Unexpected response: " + payload);
            }
        }
        else
        {
            Serial.println("Error on HTTP request: " + String(httpCode));
        }
    }
    delay(500);
}