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

void setup() {
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

void loop() {
    int leftLDR = digitalRead(LLDR);
    int rightLDR = digitalRead(RLDR);
    int centerLDR = digitalRead(CLDR);

    if (leftLDR == LOW && rightLDR == LOW && centerLDR == LOW) {
        forward();
    } else if (leftLDR == HIGH && rightLDR == LOW && centerLDR == LOW) {
        left();
    } else if (leftLDR == LOW && rightLDR == HIGH && centerLDR == LOW) {
        right();
    } else if (leftLDR == HIGH && rightLDR == HIGH && centerLDR == LOW) {
        backward();
    } else {
        stop();
    }
    
    delay(100); // Small delay to avoid rapid changes
}