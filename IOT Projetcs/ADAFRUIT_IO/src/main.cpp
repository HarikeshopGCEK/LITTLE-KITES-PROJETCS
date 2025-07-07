#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"

#define LEDPIN D4

const char *ssid = "your_wifi_ssid_here";         // Replace with your WiFi SSID
const char *password = "your_wifi_password_here"; // Replace with your WiFi password

#define IO_USERNAME "your_io_username_here" // Replace with your Adafruit IO username
#define IO_KEY "your_io_key_here"           // Replace with your Adafruit IO key
void handleMessage(AdafruitIO_Data *data);
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, password);
AdafruitIO_Feed *ledFeed = io.feed("LED"); // Make sure you have a feed named "LED" on Adafruit IO

void setup()
{
    pinMode(LEDPIN, OUTPUT);
    Serial.begin(115200);

    // Connect to Adafruit IO
    io.connect();

    // Set up a message handler for the feed
    ledFeed->onMessage(handleMessage);

    while (io.status() < AIO_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected to Adafruit IO!");
}

void loop()
{
    io.run();
}

// This function is called whenever a new value is received from Adafruit IO
void handleMessage(AdafruitIO_Data *data)
{
    String value = data->toString();
    Serial.print("Received: ");
    Serial.println(value);

    if (value == "ON" || value == "1" || value == "true")
    {
        digitalWrite(LEDPIN, HIGH);
    }
    else
    {
        digitalWrite(LEDPIN, LOW);
    }
}