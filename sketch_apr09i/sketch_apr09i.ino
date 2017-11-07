void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 2; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int k = Serial.read();
  if (k > 0) {
    lowAll();
    Serial.println(k);
    digitalWrite(k-48,HIGH);
  }
  delay(1);
}
void lowAll() {
  for (int i = 2; i < 12; i++) {
    digitalWrite(i, LOW);
  }
}
