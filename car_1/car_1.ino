.1

int FM = 5, BM = 6, LM = 9, RM = 8, r, Light = 7, tp = 11, ep = 12;
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

}

void loop() {
  // put your main code here, to run repeatedly:
  check();
  drive();
}
void check() {
  if (Serial.available()) {
    r = Serial.read();
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


