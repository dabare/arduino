#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);

int FM = 5, BM = 6, LM = 9, RM = 10, r, Light = 7, tp = 11, ep = 12;
boolean F, B, L, R, LIGHT;
long du;
void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);


  R = false;
  L = false;
  F = false;
  B = false;

  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);

  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  check();
  drive();
}
void check() {
  if (BTSerial.available()) {
    r = BTSerial.read();
    if (r == 'c') {
      L = true;
    }
    else if (r == 'l') {
      L = false;
      R = false;
    }
    else if (r == 'd') {
      R = true;
    }
    else if (r == 'a') {
      F = true;
    }
    else if (r == 'b') {
      B = true;
    }
    else if (r == 'k') {
      F = false;
      B = false;
    }
    else if (r == 'e') {
      LIGHT = true;
      digitalWrite(Light, HIGH);
      delay(20);
      digitalWrite(Light, LOW);
      delay(50);
    }
    else if (r == 'f') {
      LIGHT = false;
    }
    else if (r == 'g' || r == 'h') {
      LIGHT = !LIGHT;
    }
  }
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
    //detectObstacle();
    digitalWrite(FM, HIGH);
  } else {
    digitalWrite(FM, LOW);
  }
  if (B) {
    digitalWrite(BM, HIGH);
  } else {
    digitalWrite(BM, LOW);
  }
  if (LIGHT) {
    digitalWrite(Light, HIGH);
  } else {
    digitalWrite(Light, LOW);
  }
}

void detectObstacle() {
  getDistance();
  if (((du / 2) / 29.1) < 15) {
    digitalWrite(FM, LOW);
    digitalWrite(BM, HIGH);
    F=false;
    while (((du / 2) / 29.1) > 15) {
      getDistance();
    }
    digitalWrite(BM, LOW);
  } else {
    digitalWrite(FM, HIGH);
  }
}
void getDistance() {
  digitalWrite(tp, 0);
  delayMicroseconds(5);
  digitalWrite(tp, 1);
  delayMicroseconds(10);
  digitalWrite(tp, 0);

  pinMode(ep, INPUT);
  du = pulseIn(ep, HIGH);
}
