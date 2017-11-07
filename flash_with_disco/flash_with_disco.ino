
#define f 7
#define dd 5
void setup() {
  // put your setup code here, to run once:
  //analogWrite(21,255);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(7, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
}
int k = 5;
void loop() {
  // analogRead(20);
  flash();
}
void flash() {
  k  = random(5, 7);
  digitalWrite(f, 0);
  delay(5);
  digitalWrite(f, 1);
  digitalWrite(k, random(0,2));
  delay(110);
  analogWrite(k, 255);
  delay(40);
}



