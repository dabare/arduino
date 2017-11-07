#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BTSerial(8, 7); //TX,RX
Servo myservo;
char c;
int valA = 1, valB = 3, valC = 5, valD = 7, valE = 9, valF = 11, valK = 13, minX = 26, minY = 77, maxX = 76, maxY = 127;

int LF = 6, LB = 5, RF = 11, RB = 10;


void setup() {
  myservo.attach(3);
  myservo.write(30);
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  
  myservo.write(30);

    analogWrite(LF, 0);
      analogWrite(RF, 0);
      analogWrite(LB, 0);
      analogWrite(RB, 0);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {
    c = BTSerial.read();

    if (c == 'a') {
      analogWrite(LF, 255);
      analogWrite(RF, 255);
      analogWrite(LB, 0);
      analogWrite(RB, 0);
    } else if (c == 'd') {
      myservo.write(62);
    } else if (c == 'b') {
      analogWrite(LF, 0);
      analogWrite(RF, 0);
      analogWrite(LB, 255);
      analogWrite(RB, 255);
    } else if (c == 'c') {
      myservo.write(0);
    } //else if ((c == 'k') || (c == valC - 1)) {
    else if ((c == 'k') ) {
      analogWrite(LF, 0);
      analogWrite(RF, 0);
      analogWrite(LB, 0);
      analogWrite(RB, 0);
    } else if ( (c == 'l') ) {
      myservo.write(30);
    } 
  }

}
