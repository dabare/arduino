void setup() {
  // put your setup code here, to run once:
  analogWrite(14,255);
  analogWrite(15,0);
  
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  digitalWrite(2,1);
  digitalWrite(3,1);
  digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,0);
  digitalWrite(7,1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
