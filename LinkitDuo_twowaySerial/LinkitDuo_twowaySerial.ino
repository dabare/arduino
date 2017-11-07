

void setup() {
  // Open serial communications and wait for port to open:
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() { // run over and over
  if (Serial.available()) {
    Serial1.println(Serial.read());
  }
  if (Serial1.available()) {
     Serial.println(Serial1.read());
  }
}
