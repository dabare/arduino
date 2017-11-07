#include "analyzer.h"
int tp = 9;
int ep = 10;
long  dis();
void ssetup() {
  analogWrite(8, 255);
  analogWrite(11, 0);
  analogWrite(r, v);
  analogWrite(g, v);
  analogWrite(b, v);
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
}

void sence() {
  int d = dis();
  Serial.println(d);
  //if(d>300 && d<2500){
    analogWrite(r,200);
    
  
  //delay(250);
}

long  dis() {
  
  digitalWrite(tp, 1);
  digitalWrite(tp, 0);
  delayMicroseconds(5);
  digitalWrite(tp, 1);
  delayMicroseconds(10);
  digitalWrite(tp, 0);
  return pulseIn(ep, HIGH);
}
