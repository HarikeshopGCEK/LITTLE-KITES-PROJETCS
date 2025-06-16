#include <Arduino.h>
// All of the following definitions are equivalent
// You can use any of them to define the LED_PIN
#define LED_PIN D4
// #define LED_PIN 2
// int LED_PIN = 2;
// int LED_PIN = D4
void setup()
{
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);            // Initialize serial communication at 115200 baud rate
  Serial.println("Hello, World!"); // Print a message to the serial monitor
}

void loop()
{
  digitalWrite(LED_PIN, LOW);   // Turn the LED on
  Serial.println("LED is ON");  // Print to the serial monitor
  delay(1000);                  // Wait for a second
  digitalWrite(LED_PIN, HIGH);  // Turn the LED off
  Serial.println("LED is OFF"); // Print to the serial monitor
  delay(1000);                  // Wait for a second
}
