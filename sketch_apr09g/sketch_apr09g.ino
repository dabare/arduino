void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(12);
digitalWrite(13,1);
delay(50);
digitalWrite(13,0);
delay(50);
}
