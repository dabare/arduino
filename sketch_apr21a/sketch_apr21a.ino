void setup() {
  // put your setup code here, to run once:
analogWrite(7,255);
analogWrite(8,0);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(7,255);
analogWrite(8,0);
delay(1000);
analogWrite(7,0);
analogWrite(8,255);
delay(1000);
}
