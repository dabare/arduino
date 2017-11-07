#include "RF24.h"

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   


char inp[4]={0,0,0,0};//[id][num of swtchs][][].....switch stat
void setup(){
  Serial.begin(115200);
  //Serial1.begin(115200);

  radio.begin();
   radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();
}

byte currentChar = 0; //reading from the serial

void loop(){
  while(Serial.available()){
  inp[currentChar] = Serial.read() - '0';
  
  if(currentChar == 4 -1){
    sendCommand();
    
  }
  currentChar++;
  currentChar%=4;
 }
}

void sendCommand(){
    radio.powerUp();                                
    radio.stopListening();          

    radio.write( &inp, sizeof(inp) );
    Serial.print("sending ");
    for(int i = 0; i<sizeof(inp);i++){
      Serial.print(inp[i]);  
    }
    Serial.println();
    
    radio.startListening();                        
    
    unsigned long started_waiting_at = millis();    // Wait here until we get a response, or timeout (250ms)
    bool timeout = false;
    while ( ! radio.available()  ){
        if (millis() - started_waiting_at > 250 ){  // Break out of the while loop if nothing available
          timeout = true;
          break;
        }
    }
    
    if ( timeout ) {                                // Describe the results
      Serial.print("Time out");
    } else {
        byte data[3];
        radio.read( &data, sizeof(data) );//2nd para->size
        Serial.print("got data ");
        for(int i = 0; i<3;i++){
          Serial.print(data[i]);  
        }
        Serial.println();
    }
    radio.powerDown();
}
