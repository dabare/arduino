//WDT
#define s1 2
#define s2 3
#define s3 4
#define rst 5

#define b1 6
#define b2 7
#define b3 8

#define id 1

#define connectLight 14
#define maxSwitches 10
#define signalReadBytes 12

//#include <EEPROM.h>
#include <avr/wdt.h>
#include "RF24.h"

RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.


byte s1o = 0, s2o = 0, s3o = 0, rsto = 0;
byte s1n = 0, s2n = 0, s3n = 0, rstn = 0;

byte bulbs[signalReadBytes] = {0, 0, 0, 0, 0}; //bulbs start from 2 , 3 , 4
byte signalRead[signalReadBytes] = {0, 0, 0, 0, 0}; //id,r/w,val

void setup() {

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(rst, INPUT);

  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(connectLight, OUTPUT);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, HIGH);
  digitalWrite(b3, HIGH);

  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(rst, HIGH);

  digitalWrite(connectLight,1);
  delay(50);
  digitalWrite(connectLight,0);
  delay(50);

  digitalWrite(connectLight,1);
  delay(50);
  digitalWrite(connectLight,0);
  delay(50);

  digitalWrite(connectLight,1);
  delay(50);
  digitalWrite(connectLight,0);
  delay(50);
  
  //b1s  = EEPROM.read(b1);
  //b2s  = EEPROM.read(b2);
  //b3s  = EEPROM.read(b3);


  radio.begin();
  radio.setAutoAck(false);

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  radio.startListening();

  Serial.begin(115200);
  watchdogSetup();
}

void loop() {
  wdt_reset();
  s1n = digitalRead(s1);
  s2n = digitalRead(s2);
  s3n = digitalRead(s3);
  rstn = digitalRead(rst);
  if (s1n != s1o) {
    s1o = s1n;
    if (s1n == LOW) {
      bulbs[2] = !bulbs[2];
    }
  }

  if (s2n != s2o) {
    s2o = s2n;
    if (s2n == LOW) {
      bulbs[3] = !bulbs[3];
    }
  }

  if (s3n != s3o) {
    s3o = s3n;
    if (s3n == LOW) {
      bulbs[4] = !bulbs[4];
    }
  }

  if (rstn != rsto) {
    rsto = rstn;
    if (rstn == LOW) {
      bulbs[2] = 0;
      bulbs[3] = 0;
      bulbs[4] = 0;
    }
  }


  setBulbs();

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
      if (signalRead[1]==1) {
        for (int i = 0; i < signalReadBytes; i++) {
          bulbs[i] = signalRead[i];
        }
        // Serial.println("updated");
      }else if(signalRead[1]==2){
        bulbs[signalRead[2] + 2] = !bulbs[signalRead[2] + 2];
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

void setBulbs() {
  if (bulbs[2]) {
    setBulb(b1, HIGH);
  } else {
    setBulb(b1, LOW);
  }

  if (bulbs[3]) {
    setBulb(b2, HIGH);
  } else {
    setBulb(b2, LOW);
  }

  if (bulbs[4]) {
    setBulb(b3, HIGH);
  } else {
    setBulb(b3, LOW);
  }
}

void setBulb(byte b , boolean stat) {
  digitalWrite(b, !stat);
  //EEPROM.write(b, stat);
}

void watchdogSetup(void)
{
cli();  // disable all interrupts
wdt_reset(); // reset the WDT timer
/*
 WDTCSR configuration:
 WDIE = 1: Interrupt Enable
 WDE = 1 :Reset Enable
 WDP3 = 0 :For 2000ms Time-out
 WDP2 = 1 :For 2000ms Time-out
 WDP1 = 1 :For 2000ms Time-out
 WDP0 = 1 :For 2000ms Time-out

 WDP3 = 0 :For 1000ms Time-out
 WDP2 = 1 :For 1000ms Time-out
 WDP1 = 1 :For 1000ms Time-out
 WDP0 = 0 :For 1000ms Time-out

 WDP3 = 0 :For 1000ms Time-out
 WDP2 = 1 :For 1000ms Time-out
 WDP1 = 0 :For 1000ms Time-out
 WDP0 = 1 :For 1000ms Time-out
*/
// Enter Watchdog Configuration mode:
WDTCSR |= (1<<WDCE) | (1<<WDE);
// Set Watchdog settings:
 WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0);
sei();
}
ISR(WDT_vect) // Watchdog timer interrupt.
{
// Include your code here - be careful not to use functions they may cause the interrupt to hang and
// prevent a reset.
}
