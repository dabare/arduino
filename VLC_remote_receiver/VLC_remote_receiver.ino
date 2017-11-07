/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#include <IRremote.h>
#include "Keyboard.h"
/* 
*  Default is Arduino pin D11. 
*  You can change this to another available Arduino Pin.
*  Your IR receiver should be connected to the pin defined here
*/
int RECV_PIN = 6; 

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(5,OUTPUT);
  digitalWrite(5,0);
  pinMode(4,OUTPUT);
  digitalWrite(4,1);
  
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  Keyboard.begin();
}
 byte m = 109;
 byte space = 32;
void loop() {
  if (irrecv.decode(&results)) {
  
    switch (results.value) {
    case 10:    // left turn
      Keyboard.press(KEY_LEFT_ARROW);
      //delay(10);
      Keyboard.release(KEY_LEFT_ARROW);
      break;
    case 20:    // right turn
      Keyboard.press(KEY_RIGHT_ARROW);
      //delay(10);
      Keyboard.release(KEY_RIGHT_ARROW);
      break;
    case 40:    // up push
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
      break;
    case 60:    // your hand is nowhere near the sensor
      //Keyboard.release(KEY_UP_ARROW);
      break;
    case 160:    // right push
      Keyboard.press(KEY_RIGHT_CTRL);
      break;
    case 180:    // your hand is nowhere near the sensor
      Keyboard.release(KEY_RIGHT_CTRL);
      break;
    case 120:    // left push
      Keyboard.press(KEY_RIGHT_SHIFT);
      break;
    case 140:    // your hand is nowhere near the sensor
      Keyboard.release(KEY_RIGHT_SHIFT);
      break;
    case 80:    // down push
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
      break;
    case 100:    // your hand is nowhere near the sensor
      //Keyboard.release(KEY_DOWN_ARROW);
      break;      
  }
    irrecv.resume(); // Receive the next value
  }
}
