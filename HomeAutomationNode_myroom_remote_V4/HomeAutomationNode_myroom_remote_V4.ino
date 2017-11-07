//WDT
//auto rest on fails
#include "RF24.h"
#include <avr/wdt.h>

#define b1 2
#define b2 4
#define b3 8

#define led 3

#define signalReadBytes 12 
//delay
#define dly 250 
#define fail_threshold 3


bool b1o=0, b2o=0, b3o=0;
bool b1r=0, b2r=0, b3r=0;

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; 

byte data[signalReadBytes] = {1,2,0,0,0};//id,r/w/invert,data
byte fail = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting up...");
  radio.begin();
  radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();

  pinMode(led,OUTPUT);//led positive
  pinMode(8,OUTPUT);//led negative
  digitalWrite(8,0);

  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
  pinMode(b3,INPUT_PULLUP);
  digitalWrite(led,HIGH);
  delay(50);
  digitalWrite(led,LOW);
  delay(50);
  digitalWrite(led,HIGH);
  delay(50);
  digitalWrite(led,LOW);
  delay(50);
  digitalWrite(led,HIGH);
  delay(50);
  digitalWrite(led,LOW);
  delay(50);
  watchdogSetup();
}
byte ledStat = 0;
void loop() {
  wdt_reset();
  // put your main code here, to run repeatedly:
  b1r = digitalRead(b1);
  b2r = digitalRead(b2);
  b3r = digitalRead(b3);

  if(b3o != b3r && b3r == 0 && b1r == 0){//sw1 & sw3 are pressed
    tryBro(255);//255 is off all
    delay(dly);
  }else if(b1o != b1r && b1r == 0){
    tryBro(0);
    delay(dly);
  }else if(b2o != b2r && b2r == 0){
    tryBro(1);
    delay(dly);
  }else if(b3o != b3r && b3r == 0){
    tryBro(2);
    delay(dly);
  }

  if(ledStat==1){//off
    fail=0;
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
  }else if(ledStat==2){//on
    fail=0;
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
  }else if(ledStat==3){//connection fail
    fail++;
    if(fail==fail_threshold){
      while(1);
    }
  }else if(ledStat==4){//off all
    fail=0;
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(10);
    digitalWrite(led,LOW);
    delay(100);
  }
  
  ledStat=0;//set to nothing
  
  b1o=b1r;
  b2o=b2r;
  b3o=b3r;
}


unsigned long started_waiting_at;
bool timeout;

void tryBro(byte sw){
    digitalWrite(led,HIGH);
    radio.powerUp();                                
    radio.stopListening();          
    data[0] = 1;
    
    if(sw!=255){//255 is switch off all
      data[1] = 2;//0read 1write 2invert
      data[2] = sw;
      
      Serial.println(sw);
    }else{
      data[1] = 1;//0read 1write 2invert
      data[2] = 0;
      data[3] = 0;
      data[4] = 0;
      Serial.println("off all");
    }
    radio.write( &data, signalReadBytes);//signalReadBytes=maxSwitches + 2 
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
      ledStat = 3;//connection fail
    } else {
        radio.read( &data, signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
        if(data[sw+2]){
          ledStat=2;
        }else if(sw==-1){
          ledStat=4;
        }else{
          ledStat=1;
        }
    }
    radio.powerDown();
    digitalWrite(led,LOW);
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
