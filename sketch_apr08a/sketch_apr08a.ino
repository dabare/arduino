
void setup() // one-time actions
{
  pinMode(13, OUTPUT);
  while (true) {
    for (int i = -49; i < 50; i += 1) {

      int k = i;

      if (i < 0) {
        k = -1 * i;
      }

      digitalWrite(13, HIGH);
      delay(k ^ 2);
      digitalWrite(13, LOW);
      delay(k ^ 2);
    }
  }
}
void loop() // loop forever
{
}

