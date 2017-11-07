#define s1 2
#define s2 3
#define s3 4
#define rst 5

#define b1 6
#define b2 7
#define b3 8

#define id 0

#define connectLight 14

#include <EEPROM.h>
#include "RF24.h"

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.


byte s1o=0,s2o=0,s3o=0,rsto=0;
byte s1n=0,s2n=0,s3n=0,rstn=0;

boolean b1s = 0, b2s = 0 , b3s = 0;
byte bulbs[3] = {-1,-1,-1};

void setup() {
  
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(rst,INPUT);
  
  pinMode(b1,OUTPUT);
  pinMode(b2,OUTPUT);
  pinMode(b3,OUTPUT);
  pinMode(connectLight,OUTPUT);
  
  digitalWrite(b1,HIGH);
  digitalWrite(b2,HIGH);
  digitalWrite(b3,HIGH);
  
  b1s  = EEPROM.read(b1);
  b2s  = EEPROM.read(b2);
  b3s  = EEPROM.read(b3);
  
  
  radio.begin();
  radio.setAutoAck(false);
  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();

  Serial.begin(115200);
}

void loop() {
  s1n = digitalRead(s1);
  s2n = digitalRead(s2);
  s3n = digitalRead(s3);
  rstn = digitalRead(rst);
  if(s1n!=s1o){
   s1o = s1n;
   if(s1n==LOW){
    b1s = !b1s; 
   } 
  }

  if(s2n!=s2o){
   s2o = s2n;
   if(s2n==LOW){
    b2s = !b2s; 
   } 
  }

  if(s3n!=s3o){
   s3o = s3n;
   if(s3n==LOW){
    b3s = !b3s; 
   } 
  }

  if(rstn!=rsto){
   rsto = rstn;
   if(rstn==LOW){
    b1s = 0;
    b2s = 0;
    b3s = 0; 
   } 
  }


  setBulbs();
      
    if ( radio.available() ) {  
      digitalWrite(connectLight,HIGH);    
        bulbs[0] = b1s;
        bulbs[1] = b2s;
        bulbs[2] = b3s;

        byte data [5] = {0,0,0,0,0};  
        
        while (radio.available()) {                            
          radio.read( &data, sizeof(data) );                       
          Serial.print("Got ");
          for(int i = 0; i<5 ; i++){
              Serial.print(data[i]);
            }
            Serial.println();
        }

        if(data[0] == id){
          radio.stopListening();
          //read 1 , write 2
          if(data[1] == 1){
            radio.write( &bulbs, sizeof(bulbs) ); 
            Serial.print("Sent response ");
          }else if(data[1] == 2){
            for(int i = 0; i<3; i++){
              bulbs[i] = data[i+2];
            }
             b1s = bulbs[0];
             b2s = bulbs[1];
             b3s = bulbs[2];

             radio.write( &bulbs, sizeof(bulbs) ); 
          }                                  
          radio.startListening();   
        }      
        digitalWrite(connectLight,LOW);             
    }
}

void setBulbs(){
  if(b1s==1){
    setBulb(b1,HIGH);
  }else{
    setBulb(b1,LOW);
  }

  if(b2s==1){
    setBulb(b2,HIGH);
  }else{
    setBulb(b2,LOW);
  }

  if(b3s==1){
    setBulb(b3,HIGH);
  }else{
    setBulb(b3,LOW);
  }
}

void setBulb(byte b , boolean stat){
  digitalWrite(b,!stat);
  EEPROM.write(b, stat);
}
