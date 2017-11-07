void setup() {
  // put your setup code here, to run once:
  analogWrite(1, 10);
  analogWrite(8, 10);
  analogWrite(9, 30);
  analogWrite(4, 20);
  analogWrite(5, 100);
  analogWrite(6, 150);
  analogWrite(7, 200);
  analogWrite(8, 250);
}
int k;
void loop() {
  // put your main code here, to run repeatedly:
  for (int i = -50 ; i < 51; i++) {
    k = i;
    if (i < 0) {
      k = -i;
    }
    analogWrite(3,k);
    delay(50);
  }
}
