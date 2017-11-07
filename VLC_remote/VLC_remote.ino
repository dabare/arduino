#define MOUSE_INP1 4
#define MOUSE_INP2 5
#define BTN_UP 7
#define BTN_DWN 9
#define BTN_LFT 6
#define BTN_RT 8
#define BTN_DELAY 10
#define WHEEL_DELAY 1

#define MOUSE_CC 10
#define MOUSE_C 20
#define BTN_UP_P 40
#define BTN_UP_R 60
#define BTN_DWN_P 80
#define BTN_DWN_R 100
#define BTN_LFT_P 120
#define BTN_LFT_R 140
#define BTN_RT_P 160
#define BTN_RT_R 180

#include <IRremote.h>

IRsend irsend;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(MOUSE_INP1,INPUT_PULLUP);
  pinMode(MOUSE_INP2,INPUT_PULLUP);
  pinMode(BTN_UP,INPUT_PULLUP);
  pinMode(BTN_DWN,INPUT_PULLUP);
  pinMode(BTN_LFT,INPUT_PULLUP);
  pinMode(BTN_RT,INPUT_PULLUP);
}
byte o;
byte v[3]={0,0,0};
byte c = 0;
byte cm = 0;
byte ccm = 0;
byte mc=0;
int count = 0;
byte f=0;
byte R_UP,R_DWN,R_LFT,R_RT;
byte O_UP,O_DWN,O_LFT,O_RT;
byte r,val;
void loop() {
  // put your main code here, to run repeatedly:
  r = digitalRead(MOUSE_INP1) + digitalRead(MOUSE_INP2);
  R_UP = digitalRead(BTN_UP);
  R_DWN = digitalRead(BTN_DWN);
  R_LFT = digitalRead(BTN_LFT);
  R_RT = digitalRead(BTN_RT);
  
  if(r!=o){
    v[c] = r;
    c++;
    
    if(c==3){
      f=0;
      val = v[0]+v[1]*10+v[2]*100;
      count++;
      if(mc==3){
         mc=0;
         if(cm>ccm){
          cm=1;
          ccm=0; 
         }else{
           cm=0;
           ccm=1;
         }
      }
      if(val==12||val==201||val==120){
        f=1;
        ccm++;
        mc++;
      }else if(val==210||val==102||val==21){
        f=2;
        cm++;
        mc++;
      }else{
        if(cm>ccm){
          f=2;
        }else{
          f=1;
        }
      }
      if(f==2){
        irsend.sendSony(MOUSE_CC,12);
        delay(24);
      }else{
        irsend.sendSony(MOUSE_C,12);
        delay(24);
      }
    }
    c%=3;
  }
  o=r;

  if(O_UP!=R_UP){
    if(R_UP){
      irsend.sendSony(BTN_UP_R,12);
    }else{
      irsend.sendSony(BTN_UP_P,12);
    }
    delay(BTN_DELAY);
  }
  if(O_DWN!=R_DWN){
    if(R_DWN){
      irsend.sendSony(BTN_DWN_R,12);
    }else{
      irsend.sendSony(BTN_DWN_P,12);
    }
    delay(BTN_DELAY);
  }
  if(O_LFT!=R_LFT){
    if(R_LFT){
      irsend.sendSony(BTN_LFT_R,12);
    }else{
      irsend.sendSony(BTN_LFT_P,12);
    }
    delay(BTN_DELAY);
  }
  if(O_RT!=R_RT){
    if(R_RT){
      irsend.sendSony(BTN_RT_R,12);
    }else{
      irsend.sendSony(BTN_RT_P,12);
    }
    delay(BTN_DELAY);
  }

  O_UP=R_UP;
  O_DWN=R_DWN;
  O_LFT=R_LFT;
  O_RT=R_RT;
  delay(WHEEL_DELAY);
}
