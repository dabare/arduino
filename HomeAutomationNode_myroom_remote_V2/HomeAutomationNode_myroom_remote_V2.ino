#include "RF24.h"

#define b1 6
#define b2 5
#define b3 19

#define led 7

#define signalReadBytes 12 
//delay
#define dly 250 

bool b1o=0, b2o=0, b3o=0;
bool b1r=0, b2r=0, b3r=0;

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; 

byte data[signalReadBytes] = {1,0,0,0,0};//id,r/w,data

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial1.begin(115200);

  radio.begin();
  radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();
  
  pinMode(led,OUTPUT);//led positive
  pinMode(8,OUTPUT);//led negative
  digitalWrite(8,0);

  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);

  digitalWrite(b1,HIGH); //pull down resister
  digitalWrite(b2,HIGH); //pull down resister
  digitalWrite(b3,HIGH); //pull down resister
}
byte ledStat = 0;
void loop() {
  // put your main code here, to run repeatedly:
  b1r = digitalRead(b1);
  b2r = digitalRead(b2);
  b3r = digitalRead(b3);

  if(b1o != b1r && b1r == 0){
    delay(dly);
    tryBro(0);
  }
  if(b2o != b2r && b2r == 0){
    delay(dly);
    tryBro(1);
  }
  if(b3o != b3r && b3r == 0){
    delay(dly);
    tryBro(2);
  }

  if(ledStat==1){
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
  }else if(ledStat==2){
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
  }
  ledStat=0;
  
  b1o=b1r;
  b2o=b2r;
  b3o=b3r;
}


unsigned long started_waiting_at;
bool timeout;
void tryBro(byte sw){
    
    radio.powerUp();                                
    radio.stopListening();          
    data[0] = 1;
    data[1] = 0;
    radio.write( &data, signalReadBytes);//signalReadBytes=maxSwitches + 2 
    radio.startListening();                        
    
    started_waiting_at = millis();    // Wait here until we get a response, or timeout (250ms)
    timeout = false;
    while ( ! radio.available()  ){
        if (millis() - started_waiting_at > 250 ){  // Break out of the while loop if nothing available
          timeout = true;
          break;
        }
    }
    
    if ( timeout ) {                                // Describe the results
      ledStat = 1;
    } else {
        radio.read( &data, signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
        data[sw+2] = !data[sw+2];
        data[0]=1;
        data[1]=1;
        set();
    }
    radio.powerDown();
}

void set(){
    radio.powerUp();                                
    radio.stopListening();   
    
    radio.write( &data, signalReadBytes);//signalReadBytes=maxSwitches + 2 
    radio.startListening();                        
    
    started_waiting_at = millis();    // Wait here until we get a response, or timeout (250ms)
    timeout = false;
    
    while ( ! radio.available()  ){
        if (millis() - started_waiting_at > 250 ){  // Break out of the while loop if nothing available
          timeout = true;
          break;
        }
    }
    
    if ( timeout ) {                                // Describe the results
      ledStat = 1;
    } else {
        radio.read( &data, signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
        ledStat = 2;
    }
    radio.powerDown();
}
