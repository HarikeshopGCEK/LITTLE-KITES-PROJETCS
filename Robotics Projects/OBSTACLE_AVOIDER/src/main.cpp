#include <Arduino.h>
#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5

#define ENA 10
#define ENB 11
#define LTRIG 6
#define LECHO 7
#define RTRIG 8
#define RECHO 9

#define LSPEED 255
#define RSPEED 255

#define THRESHOLD 20 // Distance threshold in cm

float measureDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034) / 2; // Distance in cm
  return distance;
}

float Ldistance;
float Rdistance;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LTRIG, OUTPUT);
  pinMode(LECHO, INPUT);
  pinMode(RTRIG, OUTPUT);
  pinMode(RECHO, INPUT);
  digitalWrite(LTRIG, LOW);
  digitalWrite(RTRIG, LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Ldistance = measureDistance(LTRIG, LECHO);
  Rdistance = measureDistance(RTRIG, RECHO);
  Serial.print("Left Distance: ");
  Serial.print(Ldistance);
  Serial.print(" cm, Right Distance: ");
  Serial.print(Rdistance);
  Serial.println(" cm");
  if (Ldistance > THRESHOLD && Rdistance > THRESHOLD)
  {
    forward();
  }
  else if (Ldistance < THRESHOLD && Rdistance > THRESHOLD)
  {
    right();
  }
  else if (Ldistance > THRESHOLD && Rdistance < THRESHOLD)
  {
    left();
  }
  else
  {
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