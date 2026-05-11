#include <Servo.h> 
#include <Arduino.h>

Servo myservo; 

// ===================== PIN SETUP =====================
const int servoPin = 9;       // pin digital PWM untuk servo
const int btnUp = 3;

// ===================== VARIABEL =====================
int pos = 0; // sudut servo
const int PIN_LED = 3;

void setup() {

  myservo.attach(servoPin);
  Serial.begin(9600);
  pinMode(btnUp, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED"); 
  pinMode (PIN_LED, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {
  char data = Serial.read();

    if (data == '1') {
    digitalWrite (PIN_LED, HIGH);
    Serial.println("DRS: ACTIVE");
    }
  else if (data == '0') {
      digitalWrite (PIN_LED, LOW);
      Serial.println("DRS: CLOSED");
    }
  bool upState = digitalRead(btnUp);
  pos = map(val, 
            0,    // sudut minimum servo
            180); // sudut maksimum servo
  myservo.write(pos);

  // ===================== MONITORING DATA =====================
  Serial.print(val);

  Serial.print(" | Sudut Servo: ");

  // ===================== STABILISASI =====================
  delay(15); // delay kecil agar servo stabil
}