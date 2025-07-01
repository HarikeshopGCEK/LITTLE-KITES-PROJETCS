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

#define THRESHOLD 20 // Distance threshold in cm

float distance = 0.0;
float measureDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    distance = duration * 0.034 / 2; // Convert to cm
    return distance;
}
void forward() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}
void backward() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}
void left() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}
void right() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}
void stop() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
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

    if (1 < distance && distance < THRESHOLD) {
        if (digitalRead(LIR) == LOW && digitalRead(RIR) == LOW) {
            // Move forward
            forward();
        } else if (digitalRead(LIR) == HIGH && digitalRead(RIR) == LOW) {
            // Turn right
            right();
        } else if (digitalRead(LIR) == LOW && digitalRead(RIR) == HIGH) {
            // Turn left
            left();
 
        } else {
            // Stop
            stop();
        }
    } else {
        // Stop if no obstacle is detected
        stop();
    }
    delay(100); // Small delay to avoid rapid changes

}