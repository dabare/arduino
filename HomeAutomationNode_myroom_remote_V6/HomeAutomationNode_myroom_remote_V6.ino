//WDT
//auto rest on fails
//new btn library
//reset function
//status function
//split file structure
//rgb
#include "MyRoom.h"
#include <avr/wdt.h>


Receiver MyRoom(MyRoomFn);//in myroom.h
Receiver TV(TVFn);//in myroom.h
Receiver PC(PCFn);//in myroom.h
Receiver MyRoomRGB(MyRoomRGBFn);//in myroom.h
Receiver Car(CarFn);
Receiver rcvrs[] = {MyRoom, TV, PC, MyRoomRGB, Car, MyRoom, MyRoom, MyRoom};


void setup() {
  //Serial.begin(115200);
  initLeds();
  initSignal();
  initClickwheel();
  initRFID();
  currentReceiver = EEPROM.read(memAddr);
  finalDecision(currentReceiver + 1);
  watchdogSetup();
}

void loop() {
  btn_1.Update(); btn_2.Update(); btn_3.Update(); btn_L.Update(); btn_R.Update(); btn_C.Update();

  if (btn_C.clicks == -2) {
    changeReceiver();//in globals.h
  }
  if (btn_C.quickPressed) {
    checkRFID();
  }

  rcvrs[currentReceiver].Update();
  wdt_reset();


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

ISR(WDT_vect) { // Watchdog timer interrupt.

  // Include your code here - be careful not to use functions they may cause the interrupt to hang and
  // prevent a reset.
}

