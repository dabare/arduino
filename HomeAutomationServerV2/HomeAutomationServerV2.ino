#include "RF24.h"
#define maximumSerialRead 3
#define maxSwitches 10
#define signalReadBytes 12 

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   

byte switches[][maxSwitches + 3] = {             //0 byte- number of switches, 1st-unsaved changes (0-no, 1-yes) , 2nd-connection (0-no, 1-yes), 3rd onwords 16 switches
                      {3,0,1,0,0,0},
                      {3,0,1,0,0,1},
                      {8,0,1,0,0,0,0,0,0,0,0},
                      {8,0,1,0,0,0,0,0,0,0,0}
                      };


char inp[maximumSerialRead];//[id][sw][val]
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

byte currentRoom = 0;
void loop(){
  while(Serial.available()){
  inp[currentChar] = Serial.read();
  
  if(currentChar == maximumSerialRead -1){
    switches[inp[0] - '0'][1] = 1;//[current room][1] has unsaved changes
    switches[inp[0] - '0'][inp[1] - '0' + 3] = inp[2] - '0';
  }
  currentChar++;
  currentChar%=maximumSerialRead;
 }

 syncSwitch(currentRoom);
 currentRoom++;
 currentRoom%=sizeof(switches)/sizeof(switches[0]);

 //printAll();
}



void printAll(){
  Serial.print("{ \"s\":[");
  for(int i = 0; i<sizeof(switches)/sizeof(switches[0]); i++){
    Serial.print("{");
    
    Serial.print("\"id\":");
    Serial.print(i);
    Serial.print(",");
    
    Serial.print(" \"switches\":");
    Serial.print(switches[i][0]);
    Serial.print(",");

    Serial.print(" \"unsaved\":");
    Serial.print(switches[i][1]);
    Serial.print(",");

    Serial.print(" \"conn\":");
    Serial.print(switches[i][2]);
    Serial.print(",");

    Serial.print(" \"data\":");
    Serial.print("[");
    for(int j = 0; j<switches[i][0]; j++){
      Serial.print(switches[i][j+3]);
      if(j!=switches[i][0]-1){  
        Serial.print(", ");
      }
    }
    Serial.print("]");
    
    Serial.print("}");
    if(i!=sizeof(switches)/sizeof(switches[0])-1){
      Serial.print(", ");
    }
  }
   Serial.print("]}$");
}

boolean unsaved;
boolean connection;
unsigned long started_waiting_at;
bool timeout;
void syncSwitch(byte id){
    radio.powerUp();                                
    radio.stopListening();          

    unsaved = switches[id][1];
    connection = switches[id][2];

    switches[id][1] = id;
    switches[id][2] = unsaved; //(unsaved changes 0-no 1-yes) corresponds to read write

    Serial.print("Sending ");
    for(int i = 0; i<signalReadBytes;i++){
      Serial.print(switches[id][i+1]);  
    }
    Serial.println();
    
    radio.write( &switches[id][1], signalReadBytes);//signalReadBytes=maxSwitches + 2 
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
      Serial.println("time out ");
      connection = 0;
    } else {
        radio.read( &switches[id][1], signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
        unsaved = 0;
        connection = 1;
        Serial.print("got ");
        for(int i = 0; i< signalReadBytes;i++){
          Serial.print(switches[id][i+1]);  
        }
        Serial.println();
    }
    switches[id][1] = unsaved;
    switches[id][2] = connection;
    radio.powerDown();
}
