/*



  77777777777
  777777777
  -----
  IOPIUOP

*/
#include <avr/wdt.h>
#include "RF24.h"
#include "Keyboard.h"


#define id 2


RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

byte signalRead[2] = {0, 0}; //id,val

void setup() {
  radio.begin();
  radio.setAutoAck(false);

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  radio.startListening();
  Keyboard.begin();
  Serial.begin(115200);

  watchdogSetup();

}

void loop() {
  wdt_reset();

  if ( radio.available() ) {
    while (radio.available()) {
      radio.read( &signalRead, 2 );
    }

    if (signalRead[0] == id) {
      switch (signalRead[1]) {
        case 1:
          Keyboard.press(KEY_UP_ARROW);
          Keyboard.release(KEY_UP_ARROW);
          break;
        case 2:
          Keyboard.press(KEY_DOWN_ARROW);
          Keyboard.release(KEY_DOWN_ARROW);
          break;
        case 3:
          Keyboard.write(" ");
          break;
        case 4:
          Keyboard.press(KEY_LEFT_ARROW);
          Keyboard.release(KEY_LEFT_ARROW);
          break;
        case 5:
          Keyboard.press(KEY_RIGHT_ARROW);
          Keyboard.release(KEY_RIGHT_ARROW);
          break;
        case 6:
          Keyboard.write("a");
          break;
        case 7:
          Keyboard.write("b");
          break;

      }
    }
  }
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
