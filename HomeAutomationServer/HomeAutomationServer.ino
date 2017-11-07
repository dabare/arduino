#include "RF24.h"
#define maximumSerialRead 20

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   

byte switches[][17] = {             //1 byte- number of switches, 2nd onwords 16 switches
                      {3,1,1,1},
                      {3,-1,-1,-1},
                      {8,1,2,3,4,5,6,7,8}
                      };
                      
byte currentRoom = 0;

char inp[maximumSerialRead];
void setup(){
  Serial.begin(115200);

  radio.begin();
   radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();
}
byte numOfSwitches;

byte currentChar = 0; //reading from the serial
void loop(){
  while(Serial.available()){
  inp[currentChar] = Serial.read();
  
  if(currentChar == maximumSerialRead -1){
    currentRoom = inp[1] - '0';
    numOfSwitches = switches[currentRoom][0];
    
    if(inp[0] == 's'){
      setStat();
    }else if(inp[0] == 'g'){
      getStat();
    }
   }

  currentChar++;
  currentChar%=maximumSerialRead;
 }
}


void getStat(){
   radio.powerUp();                                
   radio.stopListening();          

    byte data [numOfSwitches + 2]; //number of switches + 2 for control bits
    
    data[0] = currentRoom;
    data[1] = 1; //1 for reading 2 for writing
    radio.write( &data, sizeof(data) );

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
        Serial.print(currentRoom);
        Serial.println("f");
    } else {
        Serial.print(currentRoom);
        radio.read( &data, numOfSwitches );
        for(int i = 0; i<numOfSwitches;i++){
            switches[currentRoom][i+1] = data[i];
            Serial.print(switches[currentRoom][i+1]);
        }
        Serial.println();
    }
    radio.powerDown();
}

void setStat(){
   radio.powerUp();                                
   radio.stopListening();          
   byte data [numOfSwitches + 2]; //number of switches + 2 for control bits
    
    data[0] = currentRoom;
    data[1] = 2; // control bit 2 write bites
    
    for(int i = 0; i<numOfSwitches; i++){
       data[i+2] = inp[i+3] - '0';
    }
    
    radio.write( &data, sizeof(data) );

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
      Serial.print(currentRoom);
      Serial.println("f");
    } else {
        Serial.print(currentRoom);
        radio.read( &data, numOfSwitches );
        for(int i = 0; i<numOfSwitches;i++){
            switches[currentRoom][i+1] = data[i];
        }
        Serial.println("s");
    }
    radio.powerDown();
}

