#include "RF24.h"
#define maximumSerialRead 4

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   

byte switches[][18] = {             //0 byte- number of switches, 1st-unsaved changes (0-no, 1-yes) , 2nd-connection (0-no, 1-yes), 3rd onwords 16 switches
                      {3,0,1,0,0,0},
                      {3,0,1,-1,-1,-1},
                      {8,0,1,0,0,0,0,0,0,0,0}
                      };


char inp[maximumSerialRead];//[id][num of swtchs][][].....switch stat
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
    switches[inp[0] - '0'][inp[1] - '0'] = inp[2] - '0';
  }
  currentChar++;
  currentChar%=maximumSerialRead;
 }

 syncSwitch(currentRoom);
 currentRoom++;
 currentRoom%=sizeof(switches)/sizeof(switches[0]);

 printAll();
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

void syncSwitch(byte id){
    radio.powerUp();                                
    radio.stopListening();          

    byte data [switches[id][0] + 2]; //number of switches + 2 for control bits
    
    data[0] = id; 
    data[1] = 1 + switches[id][1]; //1 for reading 2 for writing for (unsaved changes 0-no 1-yes)

    for(int i = 0; i<switches[id][0]; i++){
       data[i+2] = switches[id][i + 3];
    }
    
    radio.write( &data, sizeof(data) );
    for(int i = 0; i<sizeof(data);i++){
      //Serial.print(data[i]);  
    }
    //Serial.println();
    
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
      //Serial.print("time out ");
      if(!switches[id][1]){//does not have unsaved changes
        switches[id][2] = 0;//set to disconnect
        //Serial.print("disconnect");
      }
       //Serial.println();
    } else {
        radio.read( &data, switches[id][0] );//2nd para->size

        switches[id][2] = 1;
        if(switches[id][1]){//had unsaved changes and now done
            switches[id][1] = 0;
            currentRoom--;
            //Serial.println("changes done");
        }else{//got new data, so save
          //Serial.print("got new data ");
          for(int i = 0; i<switches[id][0];i++){
              switches[id][i+3] = data[i];
              //Serial.print(switches[id][i+3]);
          }
          //Serial.println();
        }
    }
    radio.powerDown();
}
