
#define g 3
#define r 5
#define b 6
#define del 1
#define minn 50
#define maxx 255


void setup() {
  // put your setup code here, to run once:
  briall();
}

void loop() {
chain();
}
void chain() {
  dim(g, del);
  dim(r, del);
  dim(b, del);
  //
  bri(g, del);
  bri(r, del);
  bri(b, del);

  dim(r, del);
  dim(b, del);
  dim(g, del);
  //
  bri(r, del);
  bri(b, del);
  bri(g, del);

  dim(b, del);
  dim(g, del);
  dim(r, del);
  //
  bri(b, del);
  bri(g, del);
  bri(r, del);
}

void dim(int l, int d) {
  for (int i = minn; i <= maxx; i++) {
    analogWrite(l, i);
    delay(d);
  }
}

void bri(int l, int d) {
  for (int i = maxx; i >= minn; i--) {
    analogWrite(l, i);
    delay(d);
  }
}

void dimall() {
  analogWrite(g, 255);
  analogWrite(r, 255);
  analogWrite(b, 255);
}
void briall() {
  analogWrite(g, 0);
  analogWrite(r, 0);
  analogWrite(b, 0);
}

void gr(int i) {
  dimall();
  analogWrite(g, i);
}
void bl(int i) {
  dimall();
  analogWrite(b, i);
}
void rd(int i) {
  dimall();
  analogWrite(r, i);
}

