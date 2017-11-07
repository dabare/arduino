void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int k = analogRead(0);
  if (k) {
    Serial.println((k*1000)/(1024-k));
  }
}
