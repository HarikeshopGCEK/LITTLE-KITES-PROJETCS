#include <Arduino.h>
#include <MPU6050_light.h>
#include <Wire.h>

#define LSPEED 255
#define RSPEED 255

#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5

#define ENA 10
#define ENB 11
void forward();
void backward();
void left();
void right();
void stop();
// Initialize the MPU6050 sensor
// Ensure you have the MPU6050_light library installed
MPU6050 mpu(Wire);
void setup()
{
    // Initialize serial communication for debugging
    Serial.begin(9600);
    Wire.begin();
    mpu.begin();
}
void loop()
{
    mpu.update();
    // Get the raw accelerometer and gyroscope data
    float roll = mpu.getAccX();
    float pitch = mpu.getAccY();
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" | Pitch: ");
    Serial.println(pitch);
    // Add a delay for readability
    delay(100);

    if (pitch > 1.0)
    {
        // Move forward
        Serial.println("Moving Forward");
        forward();
        // Add code to control motors for moving forward
    }
    else if (pitch < -1.0)
    {
        // Move backward
        Serial.println("Moving Backward");
        backward();
        // Add code to control motors for moving backward
    }
    else if (roll > 1.0)
    {
        // Turn right
        Serial.println("Turning Right");
        right();
        // Add code to control motors for turning right
    }
    else if (roll < -1.0)
    {
        // Turn left
        Serial.println("Turning Left");
        left();
        // Add code to control motors for turning left
    }
    else
    {
        // Stop
        Serial.println("Stopping");
        stop();
    }
}

void forward()
{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void backward()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void left()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void right()
{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, LSPEED);
    analogWrite(ENB, RSPEED);
}
void stop()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}