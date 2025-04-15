/* This code was originally written by Tatenda Tenderere in April 2025
Open with Arduino IDE

    email     :  tatendatenderere08@gmail.com 
    whatsapp  :  +263 78 643 7918  
    instagram :  supernova_orion.soa

Please do contact me 😊 ; share the code and use it for your projects ; develop it and share the development with me too. 

lets grow together ; 
*/

#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 13
#define ECHO_PIN 12
#define MAX 7000
#define SERVO_PIN 15
#define Buzzer 3

#define IN1 16   // Left forward
#define IN2 5    // Left backward
#define IN3 4   // Right forward
#define IN4 0   // Right backward
#define ENA 2
#define ENB 14

Servo myServo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX);

long readDistance() {
  return sonar.ping_cm();
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  // Stop motors initially
  stopMotors();
  digitalWrite(Buzzer, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(90);  // Center
  delay(1000);
}

void loop() {
  digitalWrite(Buzzer, LOW);
  long frontDist = scanAtAngle(90);  // Center
  Serial.print("Front: ");
  Serial.println(frontDist);

  if (frontDist < 30) {
    stopMotors();
    long leftDist = scanAtAngle(180);  // Left
    delay(500);
    Serial.print("Left: ");
    Serial.println(leftDist);

    if (leftDist < 30) {
      long rightDist = scanAtAngle(0);  // Right
      Serial.print("Right: ");
      Serial.println(rightDist);

      if (rightDist < 30) {
        digitalWrite(Buzzer, HIGH);
        Serial.println("No route!");
        delay(10000);
      } else {
        turnRight();
      }
    } else {
      turnLeft();
    }
  } else {
    moveForward();
  }
}

long scanAtAngle(int angle) {
  myServo.write(angle);
  delay(4000);  // Let servo settle
  return readDistance();
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  delay(10000);
  stopMotors();
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  delay(10000);
  stopMotors();
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(500);
}