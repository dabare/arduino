#define left_cut -50
#define right_cut 50
#define up_cut 50
#define down_cut -50
#define INCR 2
#define DECR 1
#define CLKW 2
#define CCLKW 1
#define TRI 10
int x_read, y_read , x_start , y_start , x_old, y_old, y_count,  x_count;
byte x_stat, y_stat, rotation;
void setup() {
  pinMode(A0,INPUT_PULLUP);pinMode(A1,INPUT_PULLUP);
  x_start = analogRead(A0);
  y_start = analogRead(A1);
  Serial.begin(115200);
}

void loop() {
  x_read = analogRead(A0) - x_start; y_read = analogRead(A1) - y_start;
  x_stat = 0; y_stat = 0; rotation = 0;

  if (x_read < left_cut || x_read > right_cut) {
    if (x_read < x_old) {
      x_count--;
    } else if (x_read > x_old) {
      x_count++;
    }
  }
  if (x_count < -TRI) {
    x_stat = DECR;
    x_count = 0;
  }
  if (x_count > TRI) {
    x_stat = INCR;
    x_count = 0;
  }

  if (y_read < down_cut || y_read > up_cut) {
    if (y_read < y_old) {
      y_stat = DECR;
    } else if (y_read > y_old) {
      y_stat = INCR;
    }
  }

  if (y_count < -TRI) {
    y_stat = DECR;
    y_count = 0;
  }
  if (y_count > TRI) {
    y_stat = INCR;
    y_count = 0;
  }


  if (x_stat == INCR && y_read > 0) {
    rotation = CLKW;
  } else if (x_stat == INCR && y_read < 0) {
    rotation = CCLKW;
  }
  if (x_stat == DECR && y_read > 0) {
    rotation = CCLKW;
  } else if (x_stat == DECR && y_read < 0) {
    rotation = CLKW;
  }
  if (rotation) {
    Serial.println(rotation); delay(100);
  }
  //Serial.print(x_read); Serial.print(" "); Serial.println(y_read);
  x_old = x_read; y_old = y_read;
}
