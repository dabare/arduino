#define s1 2
#define s2 3
#define s3 4
#define rst 5

#define b1 6
#define b2 7
#define b3 8

#define id 1

#define connectLight 14

 

#include <EEPROM.h>
#include "RF24.h"

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.


byte s1o=0,s2o=0,s3o=0,rsto=0;
byte s1n=0,s2n=0,s3n=0,rstn=0;

byte bulbs[3] = {0,0,0};

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
  
  //bulbs[0]  = EEPROM.read(b1);
  //bulbs[1]  = EEPROM.read(b2);
  //bulbs[2]  = EEPROM.read(b3);
  digitalWrite(s1,HIGH);
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  digitalWrite(rst,HIGH);
  
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
    bulbs[0] = !bulbs[0]; 
   } 
  }

  if(s2n!=s2o){
   s2o = s2n;
   if(s2n==LOW){
    bulbs[1] = !bulbs[1]; 
   } 
  }

  if(s3n!=s3o){
   s3o = s3n;
   if(s3n==LOW){
    bulbs[2] = !bulbs[2]; 
   } 
  }

  if(rstn!=rsto){
   rsto = rstn;
   if(rstn==LOW){
    bulbs[0] = 0;
    bulbs[1] = 0;
    bulbs[2] = 0; 
   } 
  }


  setBulbs();
      
    if ( radio.available() ) {  
        byte data [4] = {0,0,0,0};  //id,r/w,sw.no/val
        
        while (radio.available()) {                            
          radio.read( &data, sizeof(data) );                       
          Serial.print("Got ");
          for(int i = 0; i<4 ; i++){
              Serial.print(data[i]);
          }
          Serial.println();
        }

        if(data[0] == id){
          digitalWrite(connectLight,HIGH); 
          radio.stopListening();
          //read 0 , write 1
          if(data[1] == 1){
             bulbs[data[2]] = data[3];
          }
          radio.write( &bulbs, sizeof(bulbs) ); 
          Serial.print("Sent response ");
          for(int i = 0; i<3 ; i++){
              Serial.print(bulbs[i]);
          }
          Serial.println();                                  
          radio.startListening();   
        }      
        digitalWrite(connectLight,LOW);             
    }
}

void setBulbs(){
  if(bulbs[0]>0){
    setBulb(b1,HIGH);
  }else{
    setBulb(b1,LOW);
  }

  if(bulbs[1]>0){
    setBulb(b2,HIGH);
  }else{
    setBulb(b2,LOW);
  }

  if(bulbs[2]>0){
    setBulb(b3,HIGH);
  }else{
    setBulb(b3,LOW);
  }
}

void setBulb(byte b , boolean stat){
  digitalWrite(b,!stat);
  //EEPROM.write(b, stat);
}
