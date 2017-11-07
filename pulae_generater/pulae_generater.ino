
bool s = 0; bool ps = 0;
long p = 0, pulse = 0 ;
long t = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogWrite(14, 255);
  analogWrite(15, 0);
}

void loop() {
  if (analogRead(1) > 10) {
    s = 1;
  } else {
    s = 0;
  }
  if (s != ps) {
    if (s = 0) {
      p++;
      ps = s;
    } else {
      ps = s;
    }
  }
  if (t == 999999  ) {
    pulse = p;
    p = 0;
  }
  t++;
  t %= 1000000;
  
  Serial.println(pulse);
  delayMicroseconds(1);
}
