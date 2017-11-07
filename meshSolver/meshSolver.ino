#include "path.h"

path* p;
char decision = 'u';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  p = new path();
}
void loop() {
 if(Serial.available()){ Serial.println(p->action((int)Serial.read()-'0'));}


/* decision = p->action(detect());
 
 if(decision == 'u'){
   forward();
 }else if(decision == 'p'){
   park();
 }else if(decision == 'R'){
   fullTurn();
 }else if(decision == 'l'){
   turnLeft();
 }else if(decision == 'r'){
   turnRight();
 }else {
   stp();
 }*/
}

void forward(){
  Serial.println('u');
}
void park(){
  Serial.println('p');
}
void stp(){
  Serial.println('s');
}
void turnLeft(){
  Serial.println('l');
}
void turnRight(){
  Serial.println('r');
}
void fullTurn(){
  Serial.println('R');
}
int detect(){
  return (int)Serial.read()-'0';
  return 0;
}
