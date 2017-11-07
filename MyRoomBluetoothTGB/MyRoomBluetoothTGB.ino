#include <SoftwareSerial.h>

#include <EEPROM.h>
#define NORMAL 7
#define RANDOM 5
#define SMOOTH 6
#define FLASH 4

#define rp 5
#define gp 6
#define bp 3


#define rMemAddr 0
#define gMemAddr 1
#define bMemAddr 2
SoftwareSerial mySerial(10, 11); // bluetooth TX, RX


#define R 1
#define G 2
#define B 3

byte f_read = 0 , s_read, r, g, b;
bool normal = 1, randm, smooth, flash;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  mySerial.begin(9600);
  mySerial.flush();
  r = EEPROM.read(rMemAddr); g = EEPROM.read(gMemAddr); b = EEPROM.read(bMemAddr);
  //mySerial.write(r);mySerial.write(g);mySerial.write(b);
}

void loop() { // run over and over
  checkSignal();
  if (normal) {
    norm();
  }
  if (randm) {
    randomCol();
  }
  if (smooth) {
    smoothChange();
  }
  if (flash) {
    RandomFastFlash();
  }
}
void norm() {
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
}

int randomCol_speed_increment = 0;
void randomCol() {
  if (randomCol_speed_increment % 10000 == 0) {
    analogWrite(rp, random(0, r)); analogWrite(gp, random(0, g)); analogWrite(bp, random(0, b));
  }
  randomCol_speed_increment++;
}
void fastFlash() {
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
  delay(5);
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(150);
}
void RandomFastFlash() {
  analogWrite(rp, random(0, r)); analogWrite(gp, random(0, g)); analogWrite(bp, random(0, b));
  delay(5);
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(150);
}

byte smooth_lights[] {0, 0, 0};
byte smooth_inc_l = random(1, 8);
byte smooth_l = 0;
byte temp;
int smooth_speed_increment = 0;

void smoothChange() {
  if (smooth_speed_increment % 7000 == 0) {
    temp = smooth_inc_l;
    if (temp / 4) {
      if (smooth_lights[0] != r) smooth_lights[0]++;
    } else {
      if (smooth_lights[0] != 0) smooth_lights[0]--;
    }
    temp %= 4;
    if (temp / 2) {
      if (smooth_lights[1] != g) smooth_lights[1]++;
    } else {
      if (smooth_lights[1] != 0) smooth_lights[1]--;
    }
    temp %= 2;
    if (temp) {
      if (smooth_lights[2] != b) smooth_lights[2]++;
    } else {
      if (smooth_lights[2] != 0) smooth_lights[2]--;
    }

    analogWrite(rp, smooth_lights[0]); analogWrite(gp, smooth_lights[1]); analogWrite(bp, smooth_lights[2]);
    if ((smooth_lights[0] == r && r) || (smooth_lights[1] == g && g) || ( smooth_lights[2] == b && b)) {
      //smooth_inc_l = random(1, 8);
      smooth_inc_l %= 7;
      smooth_inc_l++;
    }
  }
  smooth_speed_increment++;
}


void checkSignal() {
  if (mySerial.available()) {
    f_read = mySerial.read();

    if (f_read > 3) {
      Serial.println(f_read);
      resetAll();
      switch (f_read) {
        case NORMAL:
          normal = 1;
          break;
        case SMOOTH:
          smooth = 1;
          break;
        case FLASH:
          flash = 1;
          break;
        case RANDOM:
          randm = 1;
          break;
      }
    } else {
      while (!mySerial.available());
      s_read = mySerial.read();
      Serial.print(f_read);
      Serial.print(" ");
      Serial.println(s_read);
      switch (f_read) {
        case R:
          r = s_read;
          break;
        case G:
          g = s_read;
          break;
        case B:
          b = s_read;
          break;
      }
      EEPROM.write(rMemAddr, r); EEPROM.write(gMemAddr, g); EEPROM.write(bMemAddr, b);
    }
  }
}

void resetAll() {
  normal = 0, randm = 0, smooth = 0, flash = 0;
}

