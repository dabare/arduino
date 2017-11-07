#include "RF24.h"
#include "printf.h"

#define id 1

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

byte switchStat[3] = {-1,-1,-1};
void setup(){
  Serial.begin(115200);
  Serial.println(sizeof(switchStat));
  printf_begin();
  
  radio.begin();
  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();
}

void loop(){
    
    if ( radio.available() ) {                                  
      
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
            radio.write( &switchStat, sizeof(switchStat) ); 
            Serial.print("Sent response ");
            for(int i = 0; i<3; i++){
              Serial.print(switchStat[i]);
            }
            Serial.println();
          }else if(data[1] == 2){
            radio.write( &switchStat, sizeof(switchStat) ); 
            Serial.print("Set and ent response ");
            for(int i = 0; i<3; i++){
              switchStat[i] = data[i+2];
              Serial.print(switchStat[i]);
            }
            Serial.println();
          }                                  
          radio.startListening();   
        }                 
    } else {
        Serial.println(F("Sleeping"));
        delay(50);  
    }
}
