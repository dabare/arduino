void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int k, m;
void loop() {
  // put your main code here, to run repeatedly:
  k = (analogRead(3));
  if (m != k) {
    Serial.println(k);
    m=k;
  }
  delay(100);
}
