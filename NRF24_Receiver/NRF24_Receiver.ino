#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

void setup(){
  Serial.begin(115200);
  printf_begin();
  Serial.print(F("\n\rRF24/examples/pingpair_sleepy/\n\rROLE: "));


  radio.begin();
  
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);

  // Start listening
  radio.startListening();
}

void loop(){
    
    if ( radio.available() ) {                                  
      
        byte switchStatus [5][8] = {{0,1,0,2,3,4,5,6},
                                    {2,6,9,2,3,4,5,6},
        };  
        byte inp = 0;  
        while (radio.available()) {                            
          radio.read( &inp, sizeof(byte) );                       
          printf("Got payload %d ",inp); 
        }
        radio.stopListening();                                  
        radio.write( switchStatus[inp], sizeof(switchStatus[0]) );        
        Serial.println(F("Sent response."));
        radio.startListening();                                
    } else {
        Serial.println(F("Sleeping"));
        delay(50);  
    }
}
