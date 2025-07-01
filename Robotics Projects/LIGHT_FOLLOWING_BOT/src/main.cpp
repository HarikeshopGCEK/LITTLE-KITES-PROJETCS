#include <Arduino.h>
#define LSPEED 255
#define RSPEED 255
#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5
#define ENA 10
#define ENB 11
#define LLDR 8
#define RLDR 9
#define CLDR 12
void forward()
{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}
void backward()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}
void left()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}
void right()
{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}
void stop()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
}

void setup()
{
    Serial.begin(9600);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(LLDR, INPUT);
    pinMode(RLDR, INPUT);
    pinMode(CLDR, INPUT);
}

void loop()
{
    int leftLDR = analogRead(LLDR);
    int rightLDR = analogRead(RLDR);
    int centerLDR = analogRead(CLDR);

    if (0 < centerLDR && centerLDR < 500)
    { // Adjust threshold as needed
        forward();
    }
    else if (leftLDR < 500 && rightLDR < 500)
    {
        stop(); // Stop if both LDRs are dark
    }
    else if (leftLDR < 500)
    {
        right(); // Turn right if left LDR is dark
    }
    else if (rightLDR < 500)
    {
        left(); // Turn left if right LDR is dark
    }
    else
    {
        stop(); // Stop if no LDRs are dark
    }

    delay(100); // Small delay to avoid rapid changes
}