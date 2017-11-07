void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int k , l ;
void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(3));
delay(500);
}
