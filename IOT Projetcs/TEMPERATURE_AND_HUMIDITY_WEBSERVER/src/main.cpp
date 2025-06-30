#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN 2      // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11 (AM2302)
DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);
const char *ssid = "your_SSID";         // Replace with your network SSID
const char *password = "your_PASSWORD"; // Replace with your network password
void setup()
{
    Serial.begin(115200);
    dht.begin();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/temperature", handleTemperature);
    server.on("/humidity", handleHumidity);

    server.begin();
}

void loop()
{
    server.handleClient();
}

void handleRoot()
{
    server.send(200, "text/html", "<h1>Welcome to the DHT11 Web Server</h1><p><a href=\"/temperature\">Temperature</a></p><p><a href=\"/humidity\">Humidity</a></p>");
}

void handleTemperature()
{
    float temperature = dht.readTemperature();
    if (isnan(temperature))
    {
        server.send(500, "text/plain", "Failed to read temperature");
    }
    else
    {
        server.send(200, "text/plain", String(temperature));
    }
}

void handleHumidity()
{
    float humidity = dht.readHumidity();
    if (isnan(humidity))
    {
        server.send(500, "text/plain", "Failed to read humidity");
    }
    else
    {
        server.send(200, "text/plain", String(humidity));
    }
}