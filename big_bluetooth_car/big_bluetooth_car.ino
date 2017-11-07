#define F 6
#define B 5
#define L 9
#define R 10
#define minSpeed 50
#define maxSpeed 255
#define minRemote 50
#define maxRemote 255

int i;
int curSpeed = minSpeed;

void setup() {
 
  Serial.begin(9600);

  pinMode(13,OUTPUT);
  analogWrite(F, 0);
  analogWrite(R, 0);
  analogWrite(L, 0);
  analogWrite(B, 0);

}


void loop() {
  
   
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    i = (int)Serial.read();
    if (i == 1) {
      analogWrite(F, curSpeed);
      analogWrite(B, 0);
    } else if (i == 2) {
      analogWrite(F, 0);
      analogWrite(B, curSpeed);
    } else if (i == 3) {
      analogWrite(L, 255);
      analogWrite(R, 0);
    } else if (i == 4) {
      analogWrite(L, 0);
      analogWrite(R, 255);
    }else if (i == 5)  {
      analogWrite(F, 0);
      analogWrite(B, 0);
    } else if (i == 6)  {
      analogWrite(L, 0);
      analogWrite(R, 0);
    }  else if (i >= minRemote && i<= maxRemote)  {
      curSpeed = i;
    } 
  }

}
