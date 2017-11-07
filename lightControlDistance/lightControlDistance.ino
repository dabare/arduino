int tp =11;
int ep =12;
long du;
long p;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(tp,OUTPUT);
pinMode(ep,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(tp,0);
delayMicroseconds(5);
digitalWrite(tp,1);
delayMicroseconds(10);
digitalWrite(tp,0);

pinMode(ep,INPUT);
du = pulseIn(ep,HIGH);
if(du!=p){
  p = du;
  Serial.println(p);
}

//Serial.println((du/2)/29.1);
delay(250);
}
