int i, p, c;
boolean m, l;
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  attachInterrupt(0, lol, CHANGE); //pin 2
  attachInterrupt(1, lol, CHANGE); //pin 3
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("sdfsdfsdfsd");
  delay(1000);

}
void lol() {
  m = digitalRead(2);
  l = digitalRead(3);
  if (m && l) {
    i = 3;
  } else if (m) {
    i = 2;
  } else if (l) {
    i = 1;
  } else {
    i = 0;
  }

  if (i == 0) {
    if (p == 1) {
      c++;
    } else if (p == 2) {
      c--;
    }

  } else if (i == 1) {
    if (p == 0) {
      c--;
    } else if (p == 3) {
      c++;

    }
  }
  else if (i == 2) {
    if (p == 0) {
      c++;
    } else if (p == 3) {
      c--;
    }
  } else {
    if (p == 1) {
      c--;
    } else if (p == 2) {
      c++;
    }
  }


  Serial.println(c);
}
