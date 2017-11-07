void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  for(int i = 2;i<12;i++){
    digitalWrite(i,HIGH);
  }
}
int d=100;
void loop() {
  // put your main code here, to run repeatedly:
  
   digitalWrite(2,0);
  for(int i = 2;i<10;i++){
    digitalWrite(i,LOW);
    delay(d);
    digitalWrite(i,HIGH);
  }
  for(int i = 11;i>3;i--){
    digitalWrite(i,LOW);
    delay(d);
    digitalWrite(i,HIGH);
  }
}
