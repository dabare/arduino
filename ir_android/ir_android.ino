/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

IRsend irsend;
long value;

void setup()
{
 
Serial.begin(115200);
irrecv.enableIRIn(); 
pinMode(2,OUTPUT);
digitalWrite(2,LOW);
}

void loop() {
  if (Serial.available()) {
  String s = Serial.readString();
  int str_len = s.length() + 1; 
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
   value = strtol(char_array, NULL, 16);
   if(value!=0){
     for (int i = 0; i < 3; i++) {
    irsend.sendSony(value, 12);
    delay(40);
  }}
  Serial.println(value);
  value = 0;
  }
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
