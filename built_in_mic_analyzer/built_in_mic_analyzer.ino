#include <SoftwareSerial.h>
#define r 3
#define g 5
#define b 6
#define sp 1
#define f 4
long p = 0;
long s = 0;
int v = 255;
int w = 0, minw = 245;
long mi = 1024, mx = 0, count = 0 ;
int R = 0, G = 0, B = 0 , PR = 0, PG = 0, PB = 0;
int dly = 100;
int az = 0, bz = 0, cz = 0;
int del = 0;
int tp = 9;
int ep = 10;
long dis = 0;

void analyzer();
void dimall() ;
void rgb(int RR, int GG, int BB);
void color();
void col(byte pin, int Pval, int Cval);
void setup();
void loop();
void asetup();
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
  analogWrite(8, 255); analogWrite(11, 0);
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
  asetup();
  mySerial.begin(9600);
  dimall();
  color();
}
void loop() {
  //colorflash();
  //bt();
  //flash();
  analyzer();
  //colorflash();


  /*dis =  constrain( getDis(),500,3500);
  int kkk = map(dis,500,3500,255,0);
  analogWrite(r,kkk);
  Serial.println(kkk);
  delay(100);*/
}

long getDis() {
  digitalWrite(tp, 0);
  delayMicroseconds(5);
  digitalWrite(tp, 1);
  delayMicroseconds(10);
  digitalWrite(tp, 0);
  return pulseIn(ep, HIGH);
}

void bt() {
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
void colorflash() {
  analogWrite(r, 0);
  analogWrite(g, 0);
  analogWrite(b, 0);
  delay(5);
  analogWrite(r, 255);
  analogWrite(g, 255);
  analogWrite(b, 255);
  delay(150);

}
void flash() {
  analogWrite(f, 255);
  delay(5);
  analogWrite(f, 0);
  delay(150);
}

void asetup() {
  Serial.begin(9600);
  analogWrite(14, 255);
  analogWrite(15, 0);
}

void analyzer() {
  p = pulseIn(16, HIGH);
  s =  analogRead(16);
  count = (count + 1) % 5000;

  if (count == 0) {
    mi = 1024;
    mx = 0;
  }


  w = 255 - map(s, mi, mx, 0, 255);
  if (w < minw) {
    w = minw;
  } else if (w > 255) {
    w = 55;
  }

  if (p > 100) {
    if (mi > s) {
      mi = s;
    }
    if (mx < s) {
      mx = s;
    }
    if (p < 3) {

    }
    else if (p <= 4) {

      // rgb(w, w, v);
    } else if (p <= 5) {

      // rgb(v, w, w);
    }
    else if (p <= 6) {

      //rgb(w, v, w);
    }
    else if (p <= 400) {
      rgb(1, 0, 0);
    } else if (p <= 600) {
      rgb(1, 0, 1);
    } else if (p <= 1500) {
      rgb(0, 0, 1);
    } else if (p <= 5000) {
      rgb(0, 1, 1);
    } else if (p <= 27000) {
      rgb(0, 1, 0);
    } else if (p <= 50000) {
      rgb(1, 1, 0);
    } else {
      flash();
    flash();
      //rgb(1, 1, 1);
    }
  } else {
    if(p>4){
    flash();}
    //flash();
    //rgb(0, 0, 0);
    //Serial.println(p);
  }
  /**
  del = ((mi + mx) * 1) / 3;


  if (s < del) {

    bz = az;
    az = 0;

  } else {
    az++;
  }
  **/
  if (p > 10000) {

    dly = cz;
    cz = 0;

  } else {
    cz++;
  }
  if (dly > 1500) {
    dly = 1400;
  } else if (dly < 30) {
    dly = 30;
  }
  //dly = 10400;
  //Serial.println(dly);
  color();
}

void dimall() {
  R = 0;
  G = 0;
  B = 0;
}
void rgb(int RR, int GG, int BB) {
  dimall();
  R = RR;
  G = GG;
  B = BB;
}


void color() {
  if (R) {
    col(r, PR, w);
    PR = w;
    //analogWrite(r, w);
  } else {
    col(r, PR, v);
    PR = v;
    //analogWrite(r, v);
  }
  if (G) {
    col(g, PG, w);
    PG = w;
    //analogWrite(g, w);
  } else {
    col(g, PG, v);
    PG = v;
    //analogWrite(g, v);
  }
  if (B) {
    col(b, PB, w);
    PB = w;
    //analogWrite(b, w);
  } else {
    col(b, PB, v);
    PB = v;
    //analogWrite(b, v);
  }
}
void col(byte pin, int Pval, int Cval) {
  if (Pval > Cval) {
  /*  analogWrite(pin, 0);
    delay(5);
    analogWrite(pin, 255);
    delay(150);
    analogWrite(pin, 0);
    delay(5);
    analogWrite(pin, 255);
    delay(150);*/
    for (int i = Pval; i >= Cval; i -= sp) {
      analogWrite(pin, i);
      delayMicroseconds(dly);
    }
  } else {
    analogWrite(pin, 255);
    for (int i = Pval; i <= Cval; i += sp) {
      analogWrite(pin, i);
      delayMicroseconds(dly);
    }
  }
}
