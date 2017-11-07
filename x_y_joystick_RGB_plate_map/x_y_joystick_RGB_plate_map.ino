#define R_MAX 522
#define R_MIN -501
#define G_MAX 394
#define G_MIN -413
#define B_MAX 404
#define B_MIN -402

#define rp 5
#define gp 6
#define bp 3
double sin_30, tan_30, sin_n30, tan_n30;
double x, y , x_start , y_start;
void setup() {
  sin_30 = sin(PI / 6);
  sin_n30 = sin(-1 * PI / 6);
  tan_30 = tan(PI / 6);
  tan_n30 = tan(-1 * PI / 6);

  x_start = analogRead(A0);
  y_start = analogRead(A1);
  Serial.begin(115200);
}

int R_val , G_val , B_val, m;
void loop() {
  x = analogRead(A0) - x_start;
  y = analogRead(A1) - y_start;

  R_val = y;
  G_val = -1 * sin_30 * (y + tan_n30 * x);
  B_val = -1 * sin_30 * (y + tan_30 * x);

  R_val = constrain(R_val, R_MIN, R_MAX);
  G_val = constrain(G_val, G_MIN, G_MAX);
  B_val = constrain(B_val, B_MIN, B_MAX);

  R_val = map(R_val, R_MIN, R_MAX, 0, 255);
  G_val = map(G_val, G_MIN, G_MAX, 0, 255);
  B_val = map(B_val, B_MIN, B_MAX, 0, 255);

  analogWrite(rp, R_val);
  analogWrite(gp, G_val);
  analogWrite(bp, B_val);

  Serial.print(R_val);
  Serial.print(" ");
  Serial.print(G_val);
  Serial.print(" ");
  Serial.println(B_val);

}
