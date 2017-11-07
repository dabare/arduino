#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;

int LF = 6, LB = 5, RF = 11, RB = 10;
byte FH = 14, FL = 15, BLH = 16 , BLL = 17 , BRH = 18 , BRL = 19;

int c = 0;

void setup() {
  myservo.attach(3);
  myservo.write(30);
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);

  myservo.write(30);
  // BTSerial.write(c);
  pinMode(FH, INPUT);
  pinMode(FL, INPUT);
  pinMode(BLH, INPUT);
  pinMode(BLL, INPUT);
  pinMode(BRH, INPUT);
  pinMode(BRL, INPUT);
}


void loop() {

  c = 0;
  c += digitalRead(FH) * 2;
  c += digitalRead(FL);

  if (c == 0) {
    myservo.write(30);
  } else if (c == 1) {
    myservo.write(62);
  } else if (c == 2) {
    myservo.write(0);
  }

  c = 0;
  c += digitalRead(BLH) * 2;
  c += digitalRead(BLL);

  if (c == 0) {
    analogWrite(LF, 0);
    analogWrite(LB, 0);
  } else if (c == 1) {
    analogWrite(LF, 255);
    analogWrite(LB, 0);
  } else if (c == 2) {
    analogWrite(LF, 0);
    analogWrite(LB, 255);
  }

  c = 0;
  c += digitalRead(BRH) * 2;
  c += digitalRead(BRL);

  if (c == 0) {
    analogWrite(RF, 0);
    analogWrite(RB, 0);
  } else if (c == 1) {
    analogWrite(RF, 255);
    analogWrite(RB, 0);
  } else if (c == 2) {
    analogWrite(RF, 0);
    analogWrite(RB, 255);
  }



}
