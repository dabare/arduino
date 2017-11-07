#include <Arduino.h>
#include "RF24.h"
#include "led.h"
#define CE A1
#define CSN 10

#define signalReadBytes 12
#define dly 250 //delay
#define fail_threshold 6


extern byte data[];

RF24 radio(CE, CSN);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; //pipes to communicate

extern byte data[signalReadBytes] = {1, 2, 0, 0, 0}; //id,r/w/invert,data

byte fail = 0;// signal failier

void initSignal() {
  radio.begin();
  radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.powerDown();
}


unsigned long started_waiting_at;
bool timeout;

boolean txrx() {
  digitalWrite(ledsig, HIGH);

  radio.powerUp();
  radio.stopListening();

  radio.write( &data, signalReadBytes);//signalReadBytes=maxSwitches + 2
  radio.startListening();

  started_waiting_at = millis();    // Wait here until we get a response, or timeout (250ms)
  timeout = false;
  while ( ! radio.available()  ) {
    if (millis() - started_waiting_at > 250 ) { // Break out of the while loop if nothing available
      timeout = true;
      break;
    }
  }
  if ( timeout ) {                                // Describe the results
    //connection fail
    fail++;
    if (fail == fail_threshold) {
      while (1);
    }
  } else {
    radio.read( &data, signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
    fail = 0;
  }
  radio.powerDown();

  digitalWrite(ledsig, LOW);

  if (fail) return 0;
  return 1;
}

void tx_twobytes() {//id,signal
  digitalWrite(ledsig, HIGH);
  radio.powerUp();
  radio.stopListening();

  radio.write( &data, 2);//single byte from data
  
  radio.powerDown();

  digitalWrite(ledsig, LOW);
}


void tx_threebytes() {//id,data,data
  digitalWrite(ledsig, HIGH);
  radio.powerUp();
  radio.stopListening();

  radio.write( &data, 3);//single byte from data
  
  radio.powerDown();

  digitalWrite(ledsig, LOW);
}
