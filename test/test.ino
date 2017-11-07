#define left_cut -1
#define right_cut 1
#define up_cut 2
#define down_cut -2
#define INCR 2
#define DECR 1
#define CLKW 2
#define CCLKW 1
#define TRI 50
int x_read, y_read , x_start , y_start , x_old, y_old, y_count,  x_count;
byte x_stat, y_stat, rotation;
void setup() {
  pinMode(A0,INPUT_PULLUP);pinMode(A1,INPUT_PULLUP);
  x_start = analogRead(A0);
  y_start = analogRead(A1);
  Serial.begin(115200);
}

void loop() {
  x_read = analogRead(A0) ; y_read = analogRead(A1);
 
    Serial.println(x_read); 
}
