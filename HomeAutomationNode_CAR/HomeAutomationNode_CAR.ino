
#include <avr/wdt.h>
#include "RF24.h"
#include "Keyboard.h"
#include <Servo.h>

#define id 5
#define FWRD 5
#define RVS 3
#define STR 7
#define signal_length 2
Servo myservo;
RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

byte signalRead[signal_length] = {0, 0}; //id,meta(fwd-1/rec-2/stop-0-3,left-1/right-2/center-0-3)
//                                            [][00, 00, 0000]
void setup() {
  radio.begin();
  radio.setAutoAck(false);

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  myservo.attach(STR);
  radio.startListening();
  Serial.begin(115200);
  myservo.write(100);
  watchdogSetup();
}

bool L, R, C, F, B;
byte   temp;
int i = 0;
void loop() {
  wdt_reset();

  if ( radio.available() ) {
    while (radio.available()) {
      radio.read( &signalRead, signal_length );
    }
    if (signalRead[0] == id) {
      temp = signalRead[1];
      B = temp / 128;
      temp %= 128;
      F = temp / 64;
      temp %= 64;
      R = temp / 32;
      temp %= 32;
      L = temp / 16;
      Serial.print(i++);
      Serial.print(" ");
      Serial.print(L);
      Serial.print(" ");
      Serial.print(R);
      Serial.print(" ");
      Serial.print(F);
      Serial.print(" ");
      Serial.println(B);
    }
  }
  if (L && !R) {
    myservo.write(123);
  } else if (R && !L) {
    myservo.write(69);
  } else {
    myservo.write(100);
  }

  analogWrite(FWRD, 255);
  analogWrite(RVS, 255);
  if (F) {
    analogWrite(FWRD, 0);
  } else if (B) {
    analogWrite(RVS, 0);
  }
}


void watchdogSetup(void) {
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
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // Set Watchdog settings:
  WDTCSR = (1 << WDIE) | (1 << WDE) | (0 << WDP3) | (1 << WDP2) | (0 << WDP1) | (1 << WDP0);
  sei();
}
ISR(WDT_vect) // Watchdog timer interrupt.
{
  // Include your code here - be careful not to use functions they may cause the interrupt to hang and
  // prevent a reset.
}
