//WDT
//auto rest on fails
//debounce fix
//reset function
//status function
#include "RF24.h"
#include <avr/wdt.h>

#define signalReadBytes 12 
#define dly 250 //delay
#define fail_threshold 6


#define sw1p 2
#define sw2p 4
#define sw3p 8
#define swrstp 7
#define swsttp 14
#define led1 3
#define led2 5
#define led3 6
#define ledsig 19
#define ledMaxPow 10
#define ledMinPow 0


#define loopDelay 5
#define checkDelay 10
#define debounceDelay 50 // the debounce time; increase if the output flickers

struct button{
  byte pin;//pin
  byte id;// identity
  bool buttonState;// the current reading from the input pin
  bool lastButtonState;// the previous reading from the input pin
  unsigned long lastDebounceTime;// the last time the output pin was toggled
};

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; //pipes to communicate

byte data[signalReadBytes] = {1,2,0,0,0};//id,r/w/invert,data

byte fail = 0;// signal failier
byte request = 0;
button sw1={sw1p,0,0,0,0},sw2={sw2p,1,0,0,0},sw3={sw3p,2,0,0,0},swrst={swrstp,3,0,0,0},swstt={swsttp,4,0,0,0};
void setup() {
  pinMode(led1, OUTPUT);pinMode(led2, OUTPUT);pinMode(led3, OUTPUT);pinMode(ledsig, OUTPUT);
  pinMode(sw1.pin, INPUT_PULLUP);pinMode(sw2.pin, INPUT_PULLUP);pinMode(sw3.pin, INPUT_PULLUP);pinMode(swrst.pin, INPUT_PULLUP);pinMode(swstt.pin, INPUT_PULLUP);

  pinMode(18, OUTPUT);//ledsig negative pin
  digitalWrite(18, 0);
  
  Serial.begin(115200);
  radio.begin();
  radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
 
  radio.powerDown();

  watchdogSetup();

  for(int i = ledMinPow; i <= ledMaxPow; i++){
    analogWrite(led3,i);
    delay(loopDelay);  
  }
  for(int i = ledMinPow; i <= ledMaxPow; i++){
    analogWrite(led2,i);
    delay(loopDelay);  
  }
  for(int i = ledMinPow; i <= ledMaxPow; i++){
    analogWrite(led1,i);
    delay(loopDelay);  
  }

  for(int i = ledMaxPow; i >= ledMinPow; i--){
    analogWrite(led3,i);
    delay(loopDelay);  
  }
  for(int i = ledMaxPow; i >= ledMinPow; i--){
    analogWrite(led2,i);
    delay(loopDelay);  
  }
  for(int i = ledMaxPow; i >= ledMinPow; i--){
    analogWrite(led1,i);
    delay(loopDelay);  
  }
}

void loop() {
  wdt_reset();
  if(!fail){
    switch(request){
      case 1://invert 0
        if(data[2]){
          analogWrite(led1,ledMaxPow);
          delay(50);
          analogWrite(led1,ledMinPow);
          delay(50);

          analogWrite(led1,ledMaxPow);
          delay(50);
          analogWrite(led1,ledMinPow);
        }else{
          analogWrite(led1,ledMaxPow);
          delay(150);
          analogWrite(led1,ledMinPow);
        }
        break;
      case 2://invert 1
        if(data[3]){
          analogWrite(led2,ledMaxPow);
          delay(50);
          analogWrite(led2,ledMinPow);
          delay(50);

          analogWrite(led2,ledMaxPow);
          delay(50);
          analogWrite(led2,ledMinPow);
        }else{
          analogWrite(led2,ledMaxPow);
          delay(150);
          analogWrite(led2,ledMinPow);
        }
        break;
      case 3://invert 2
        if(data[4]){
          analogWrite(led3,ledMaxPow);
          delay(50);
          analogWrite(led3,ledMinPow);
          delay(50);

          analogWrite(led3,ledMaxPow);
          delay(50);
          analogWrite(led3,ledMinPow);
        }else{
          analogWrite(led3,ledMaxPow);
          delay(150);
          analogWrite(led3,ledMinPow);
        }
        break;
      case 4://reset all
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led3,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led2,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led1,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMaxPow; i >= ledMinPow; i--){
          analogWrite(led1,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMaxPow; i >= ledMinPow; i--){
          analogWrite(led2,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMaxPow; i >= ledMinPow; i--){
          analogWrite(led3,i);
          delay(checkDelay);  
        }
        break;
      case 5:
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led3,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led2,i);
          delay(checkDelay);  
        }
        wdt_reset();
        for(int i = ledMinPow; i <= ledMaxPow; i++){
          analogWrite(led1,i);
          delay(checkDelay);  
        }

        if(data[2]||data[3]||data[4]){
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led1,i);analogWrite(led2,i);analogWrite(led3,i);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMinPow; i <= ledMaxPow; i++){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMinPow; i <= ledMaxPow; i++){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMinPow; i <= ledMaxPow; i++){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led1,i * data[2]);analogWrite(led2,i * data[3]);analogWrite(led3,i * data[4]);
            delay(checkDelay);  
          }
        }else{
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led1,i);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led2,i);
            delay(checkDelay);  
          }
          wdt_reset();
          for(int i = ledMaxPow; i >= ledMinPow; i--){
            analogWrite(led3,i);
            delay(checkDelay);  
          }
        }
        break;
    }
    request = 0;
  }
  checkSwitch(&sw1);
  checkSwitch(&sw2);
  checkSwitch(&sw3);
  checkSwitch(&swrst);
  checkSwitch(&swstt);
}

byte reading;
void checkSwitch(button* sw){
  reading = digitalRead(sw->pin);
  if (reading != sw->lastButtonState) {
    sw->lastDebounceTime = millis();
  }

  if ((millis() - sw->lastDebounceTime) > debounceDelay) {
    if (reading != sw->buttonState) {
      sw->buttonState = reading;
      
      if (sw->buttonState == LOW) {
        push(&sw->id);
      }
    }
  }
  sw->lastButtonState = reading;
}


unsigned long started_waiting_at;
bool timeout;

void push(byte* id){
  digitalWrite(ledsig,HIGH);
  
  radio.powerUp();                                
  radio.stopListening();          
  data[0] = 1;

  switch(*id){
    case 0://invert 0
      data[1] = 2; //0read 1write 2invert
      data[2] = 0; //inverting switch
      request = 1;
      break;
    case 1://invert 1
      data[1] = 2; //0read 1write 2invert
      data[2] = 1; //inverting switch
      request = 2;
      break;
    case 2://invert 2
      data[1] = 2; //0read 1write 2invert
      data[2] = 2; //inverting switch
      request = 3;
      break;
    case 3://reset all
      data[1] = 1;//0read 1write 2invert
      data[2] = 0;
      data[3] = 0;
      data[4] = 0;
      request = 4;
      break;
    case 4:
      data[1] = 0;//0read 1write 2invert
      request = 5;
      break;
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
      //connection fail
      fail++;
      if(fail==fail_threshold){
        while(1);
      }
    } else {
        radio.read( &data, signalReadBytes);//2nd para->size//switches[id][1] because two control bits follow the values
        fail = 0;
    }
  radio.powerDown();

  digitalWrite(ledsig,LOW);
}


void watchdogSetup(void){
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

ISR(WDT_vect){ // Watchdog timer interrupt.

// Include your code here - be careful not to use functions they may cause the interrupt to hang and
// prevent a reset.
}
