
#define f 7
#define dd 5
void setup() {
  pinMode(f,OUTPUT);
}

void loop() {
 // analogRead(20);
flash();
}
void flash() {
 digitalWrite(f, 1);
  delay(5);
  digitalWrite(f, 0);
  delay(150);
}



