#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const char *ssid = "your_SSID"; // Replace with your WiFi SSID
const char *password = "your_PASSWORD"; // Replace with your WiFi password

const char *yourWriteAPIKey = "your_WRITE_API_KEY"; // Replace with your ThingSpeak Write API Key
const char *yourChannelID = "your_CHANNEL_ID"; // Replace with your ThingSpeak Channel ID

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
void setup(){
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop(){
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    if (isnan(temp) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C");
    Serial.print(" | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Update ThingSpeak with the new values
    ThingSpeak.setField(1, temp);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.writeFields(yourChannelID, yourWriteAPIKey);
}