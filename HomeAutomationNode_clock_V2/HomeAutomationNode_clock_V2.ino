
#define id 3

#define connectLight 14
#define maxSwitches 10
#define signalReadBytes 12

//#include <EEPROM.h>
#include "RF24.h"
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"

RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentExtended      display(PIN_CLK, PIN_DIO);

byte s1o = 0, s2o = 0, s3o = 0, rsto = 0;
byte s1n = 0, s2n = 0, s3n = 0, rstn = 0;

byte bulbs[signalReadBytes] = {0, 0, 0, 59, 0}; //bulbs start from 2 , 3 , 4
byte signalRead[signalReadBytes] = {0, 0, 0, 0, 0}; //id,r/w,val

void setup() {

  pinMode(connectLight, OUTPUT);

  display.begin();            // initializes the display
  display.setBacklight(50); 
  
  radio.begin();
  radio.setAutoAck(false);

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  radio.startListening();

  Serial.begin(115200);
}

void loop() {
  display.printTime(bulbs[2], bulbs[3], true);
  
  if ( radio.available() ) {
    while (radio.available()) {
      radio.read( &signalRead, signalReadBytes );
      //Serial.print("Got ");
      //for(int i = 0; i<signalReadBytes ; i++){
      //    Serial.print(signalRead[i]);
      //   Serial.print(',');
      //}
      //Serial.println();
    }

    if (signalRead[0] == id) {
      digitalWrite(connectLight, HIGH);
      radio.stopListening();
      radio.flush_tx();
      //read 0 , write 1
      if (signalRead[1]) {
        for (int i = 0; i < signalReadBytes; i++) {
          bulbs[i] = signalRead[i];
        }
        // Serial.println("updated");
      }
      radio.write( &bulbs, signalReadBytes );
      // Serial.print("Sent response ");
      // for(int i= 0; i<signalReadBytes; i++){
      //  Serial.print(bulbs[i]);
      //  Serial.print(',');
      //}
      //Serial.println();
      radio.startListening();
    }
    digitalWrite(connectLight, LOW);
  }
}

