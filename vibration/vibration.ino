void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  analogWrite(6, 255);
  delay(50);
}

void loop() {
  // put your main code here, to run repeatedly:

a();
delay(1000);
c();
}


void a() {
  for (int i = 100 ; i < 256; i++) {
    analogWrite(6, i);
    delay(10);
  }

}
void b() {
    analogWrite(6, 255);
    delay(900);

    analogWrite(6, 0);
    delay(400);
}
void c(){
  for (int i = 255; i>99;i--){
  analogWrite(6, i);
    delay(10);
  }
}
