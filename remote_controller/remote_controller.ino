#include <SoftwareSerial.h>

int A = 4, B = 12, C = 11, D = 14, E = 15, F = 16, K = 17, X = 7 , Y = 6;
int valA = 1, valB = 3, valC = 5, valD = 7, valE = 9, valF = 11, valK = 13, minX = 26, minY = 77, maxX = 76, maxY = 127;
char MX, MY, PY, PX, t ;
boolean PA, PB, PC, PD, PE, PF, PK;

SoftwareSerial BTSerial(8, 7); //TX,RX



void setup() {
  // put your setup code here, to run once:

  BTSerial.begin(9600);
  Serial.begin(9600);

  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  pinMode(E, INPUT);
  pinMode(F, INPUT);
  pinMode(K, INPUT);

  PA = digitalRead(A);
  PB = digitalRead(B);
  PC = digitalRead(C);
  PD = digitalRead(D);
  PE = digitalRead(E);
  PF = digitalRead(F);
  PK = digitalRead(K);

  MX = map(analogRead(X), 0, 1023, 26, 76);
  MY = map(analogRead(Y), 0, 1023, 77, 127);

  PX = MX;
  PY = MY;


  //resetBT();
}
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(A) != PA) {
    PA = !PA;
    Send(valA - PA);
  }

  if (digitalRead(B) != PB) {
    PB = !PB;
    Send(valB - PB);
  }

  if (digitalRead(C) != PC) {
    PC = !PC;
    Send(valC - PC);
  }

  if (digitalRead(D) != PD) {
    PD = !PD;
    Send(valD - PD);
  }

  if (digitalRead(E) != PE) {
    PE = !PE;
    Send(valE - PE);
  }

  if (digitalRead(F) != PF) {
    PF = !PF;
    Send(valF - PF);
  }

  if (digitalRead(K) != PK) {
    PK = !PK;
    Send(valK - PK);
  }
  t = map(analogRead(X), 0, 1023, minX, maxX);
  if (t != PX) {
    PX = t;
    Send(PX);
  }

  t =  map(analogRead(Y), 0, 1023, minY, maxY);
  if (t != PY) {
    PY = t;
    Send(PY);
  }



 // if (BTSerial.available()) {
  //}


}

void Send(char c) {
  BTSerial.write(c);
}




