#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_PIN 2 // GPIO pin for the LED

// Credetials for WiFi connection
char ssid[] = "your-ssid";         // Replace with your network SSID
char password[] = "your-password"; // Replace with your network password
WiFiServer server(80);             // Create a server that listens on port 80
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

String htmlPage = "<!DOCTYPE html>"
                  "<html>"
                  "<head><title>ESP8266 LED Control</title></head>"
                  "<body>"
                  "<h1>Control the LED</h1>"
                  "<p><a href=\"/LED=ON\"><button>Turn ON</button></a></p>"
                  "<p><a href=\"/LED=OFF\"><button>Turn OFF</button></a></p>"
                  "</body>"
                  "</html>";
void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients
  if (!client)
  {
    Serial.println("No client connected");
    return;
  }
  while (!client.available())
  {
    delay(1); // Wait for data from the client
  }
  {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("/LED=ON") != -1)
    {
      digitalWrite(LED_PIN, HIGH);
    }
    else if (request.indexOf("/LED=OFF") != -1)
    {
      digitalWrite(LED_PIN, LOW);
    }

    // Send the HTML page
    client.print(htmlPage);
  }
}
