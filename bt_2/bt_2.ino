#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

//z = up down
//x = width
//y = height




char c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("enter at command");
  BTSerial.begin(9600);
}
float vx, vy, vz, ox, oy, oz;
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
  if (oy != vy) {
    Serial.println(vy);
    oy = vy;
  }
  if (ox != vx) {
    //Serial.println(vx);
    ox = vx;
  }
  if (oz != vz) {
   // Serial.println(vz);
    oz = vz;
  }
  if (Serial.available())
    BTSerial.write(Serial.read());

}
