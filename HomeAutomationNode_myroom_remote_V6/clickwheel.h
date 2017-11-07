#define p1 A4
#define p2 A3

void initClickwheel() {
  pinMode(p1, INPUT_PULLUP);
  pinMode(p2, INPUT_PULLUP);
}
byte o;
byte v[3] = {0, 0, 0};
byte c = 0;
byte cm = 0;
byte ccm = 0;
byte mc = 0;
int count = 0;
byte f = 0;
byte r = 0;
byte val = 0;

byte cliclWheelUpdate() {
  // put your main code here, to run repeatedly:
  r = digitalRead(p1) + digitalRead(p2);

  if (r != o) {
    v[c] = r;
    c++;

    if (c == 3) {
      f = 0;
      val = v[0] + v[1] * 10 + v[2] * 100;
      //Serial.print(count);
      //Serial.print(" ");
      count++;
      if (mc == 3) {
        mc = 0;
        if (cm > ccm) {
          cm = 1;
          ccm = 0;
        } else {
          cm = 0;
          ccm = 1;
        }
      }
      if (val == 12 || val == 201 || val == 120) {
        f = 1;
        ccm++;
        mc++;
      } else if (val == 210 || val == 102 || val == 21) {
        f = 2;
        cm++;
        mc++;
      } else {
        if (cm > ccm) {
          f = 2;
        } else {
          f = 1;
        }
      }
      return f;
    }
    c %= 3;
  }
  o = r;
  delay(1);
  return 0;
}
