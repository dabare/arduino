#include <SoftwareSerial.h>


SoftwareSerial BTSerial(2, 3);

int FM = 5, BM = 6, LM = 9, RM = 10, tmp;


//z = up down
//x = width
//y = height


char c;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("enter at command");
  BTSerial.begin(9600);
  pinMode(LM, OUTPUT);
  pinMode(RM, OUTPUT);
}
float vx, vy, vz;
boolean x, y, z;
String X, Y, Z;
void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {
    c = BTSerial.read();
    if (c != '\n') {
      if (c != ' ') {
        if (c != ':') {
          if (c == 'X') {
            x = true;
            y = false;
            z = false;
            X = "";
          } else if (c == 'Y') {
            x = false;
            y = true;
            z = false;
            Y = "";
          } else if (c == 'Z') {
            x = false;
            y = false;
            z = true;
            Z = "";
          } else if (x) {
            X += c;
          } else if (y) {
            Y += c;
          } else if (z) {
            Z += c;
          }
        }
      }
    }
  }

  if (!z) {
    vz = Z.toFloat();
  }
  if (!y) {
    vy = Y.toFloat();
  }
  if (!x) {
    vx = X.toFloat();
  }

  if (vz < 0.0) {


    if (vx < -0.30) {
      if (vx < -0.98) {
        vx = -1.0;
      }
      // Serial.println("Back");
      tmp = vx * -1.0 * 100;
      tmp = map(tmp, 30, 100, 50, 255);
      analogWrite(BM, tmp);
      analogWrite(FM, 0);
    } else if (vx > 0.30) {
      if (vx > 0.98) {
        vx = 1.0;
      }
      // Serial.println("Front");
      tmp = vx * 100;
      tmp = map(tmp, 30, 100, 50, 255);
      analogWrite(FM, tmp);
      analogWrite(BM, 0);
    } else {

      analogWrite(FM, 0);
      analogWrite(BM, 0);
    }


    if (vy < -0.30) {
      if (vy < -0.98) {
        vy = -1.0;
      }
      //Serial.println("Right");
      digitalWrite(RM, HIGH);
      digitalWrite(LM, LOW);
    } else if (vy > 0.30) {
      if (vy > 0.98) {
        vy = 1.0;
      }
      // Serial.println("Left");

      digitalWrite(RM, LOW);
      digitalWrite(LM, HIGH);
    } else {
      digitalWrite(LM, LOW);
      digitalWrite(RM, LOW);
    }
  } else {
    analogWrite(FM, 0);
    analogWrite(BM, 0);
    digitalWrite(LM, LOW);
    digitalWrite(RM, LOW);
  }

  if (Serial.available())
    BTSerial.write(Serial.read());

}
