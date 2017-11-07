//----------------------Motors-----------------
#define MLF 9
#define MLB 10
#define MRF 5
#define MRB 6
//----------------------Sensors-----------------
#define SJL 11
#define SJR 2
#define SPR 3
#define SPL 4
#define SJF 12
#define SJY 13

#define maxMotor 255
#define blackPath 1


void setup() {
  pinMode(8, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


  digitalWrite(2, HIGH);

  digitalWrite(3, HIGH);

  digitalWrite(4, HIGH);

  digitalWrite(11, HIGH);

  digitalWrite(12, HIGH);

  digitalWrite(13, HIGH);

  Serial.begin(9600);


}

void loop() {
  followLine();
}


void followLine() {
  if (readPin(SJF) && !readPin(SJL) && readPin(SJR)) {
    while (readPin(SJF)) {
      rightMotorForward();
      leftMotorBackward();
    }
    stopLeftMotor();
    stopRightMotor();
  } else if (readPin(SJF) && readPin(SJL) && !readPin(SJR)) {
    while (readPin(SJF)) {
      leftMotorForward();
      rightMotorBackward();
    }
    stopLeftMotor();
    stopRightMotor();
  }
  else if (readPin(SPL) && !readPin(SPR)) {
    stopRightMotor();
    leftMotorForward();
  } else if (readPin(SPR) && !readPin(SPL)) {
    stopLeftMotor();
    rightMotorForward();
  } else if (!readPin(SPR) && !readPin(SPL)) {
    leftMotorForward();
    rightMotorForward();
  } else {
    stopRightMotor();
    stopLeftMotor();
  }
}


void leftMotorForward() {
  analogWrite(MLF, maxMotor);
  analogWrite(MLB, 0);
}
void rightMotorForward() {
  analogWrite(MRF, maxMotor);
  analogWrite(MRB, 0);
}
void leftMotorBackward() {
  analogWrite(MLF, 0);
  analogWrite(MLB, maxMotor);
}
void rightMotorBackward() {
  analogWrite(MRF, 0);
  analogWrite(MRB, maxMotor);
}
void stopRightMotor() {
  analogWrite(MRF, 0);
  analogWrite(MRB, 0);
}
void stopLeftMotor() {
  analogWrite(MLF, 0);
  analogWrite(MLB, 0);
}
bool readPin(int pin) {
  bool stat = false;
  digitalWrite(pin, LOW);
  delayMicroseconds(200);
  stat = digitalRead(8);
  digitalWrite(pin, HIGH);
  return blackPath - stat;
}
