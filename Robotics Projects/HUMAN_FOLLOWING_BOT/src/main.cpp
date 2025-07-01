#include <Arduino.h>

#define LSPEED 255
#define RSPEED 255

#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5

#define ENA 10
#define ENB 11

#define LIR 8
#define RIR 9

#define ECHO 6
#define TRIG 7

float distance = 0.0;
void measureDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    distance = duration * 0.034 / 2; // Convert to cm
}
void setup(){
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(LIR, INPUT);
    pinMode(RIR, INPUT);
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
}
void loop(){
    distance = measureDistance();

    if (distance < 20) {
        if (digitalRead(LIR) == LOW && digitalRead(RIR) == LOW) {
            // Move forward
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
        } else if (digitalRead(LIR) == HIGH && digitalRead(RIR) == LOW) {
            // Turn right
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, LOW);
            digitalWrite(RM2, HIGH);
        } else if (digitalRead(LIR) == LOW && digitalRead(RIR) == HIGH) {
            // Turn left
            digitalWrite(LM1, LOW);
            digitalWrite(LM2, HIGH);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
        } else {
            // Stop
            digitalWrite(LM1, LOW);
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, LOW);
            digitalWrite(RM2, LOW);
        }
    } else {
        // Stop if no obstacle is detected
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
    }
    delay(100); // Small delay to avoid rapid changes

}