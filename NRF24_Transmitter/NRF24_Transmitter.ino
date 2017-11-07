#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   

void setup(){
  Serial.begin(115200);
  printf_begin();

  radio.begin();

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();
}

void loop(){
  if(Serial.available()){
    radio.powerUp();                                // Power up the radio after sleeping
    radio.stopListening();                          // First, stop listening so we can talk.
                  Serial.read();
                  Serial.flush();       
    byte inp = 0;                     
    printf("sending... %d ", inp);
   // Serial.println(time);
    
    radio.write( &inp, sizeof(byte) );

    radio.startListening();                         // Now, continue listening
    
    unsigned long started_waiting_at = millis();    // Wait here until we get a response, or timeout (250ms)
    bool timeout = false;
    while ( ! radio.available()  ){
        if (millis() - started_waiting_at > 250 ){  // Break out of the while loop if nothing available
          timeout = true;
          break;
        }
    }
    
    if ( timeout ) {                                // Describe the results
        Serial.println(F("Failed, response timed out."));
    } else {
       byte switchStatus [8] = {0,0,0,0,0,0,0,0};   
        radio.read( &switchStatus, sizeof(switchStatus) );
    
        printf("Got response");
        for(int i = 0; i<8;i++){
            printf("%d",switchStatus[i]);
          }
          printf("\n");
    }
    
    radio.powerDown();
  }
}

