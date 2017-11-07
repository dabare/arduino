#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);

int FM = 6, BM = 7, LM = 8, RM = 9,r;
boolean F, B, L, R;
int c = 99, l = 108, d = 100, a = 97, k = 107, b = 98;
void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
 
 Serial.begin(9600);
 
  
  R = false;
  L = false;
  F = false;
  B = false;
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 F=true;
 B=false;
  drive();
  delay(200);
  F=false;
  B=true;
  drive();
  delay(200);
}

void drive() {
  if (R) {
    digitalWrite(RM, HIGH);
  } else {
    digitalWrite(RM, LOW);
  }
  if (L) {
    digitalWrite(LM, HIGH);
  } else {
    digitalWrite(LM, LOW);
  }
  if (F) {
    digitalWrite(FM, HIGH);
  } else {
    digitalWrite(FM, LOW);
  }
  if (B) {
    digitalWrite(BM, HIGH);
  } else {
    digitalWrite(BM, LOW);
  }

}
