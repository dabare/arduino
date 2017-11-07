int sleep,l,h;
void setup() {
  // put your setup code here, to run once:
  sleep=50;
  l=10;
  h=250;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  analogWrite(11,h);
  analogWrite(10,l);
  analogWrite(6,l);
  analogWrite(5,l);
  delay(sleep);
  
  analogWrite(11,l);
  analogWrite(10,h);
  analogWrite(6,l);
  analogWrite(5,l);
  delay(sleep);
  
  analogWrite(11,l);
  analogWrite(10,l);
  analogWrite(6,h);
  analogWrite(5,l);
  delay(sleep);
  
  analogWrite(11,l);
  analogWrite(10,l);
  analogWrite(6,l);
  analogWrite(5,h);
  delay(sleep);
}
