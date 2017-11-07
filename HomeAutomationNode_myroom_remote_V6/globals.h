#include "Receiver.h"
#include "signal.h"
#include <EEPROM.h>
#include <avr/wdt.h>

#define sw1p 2  //1
#define sw2p 4  //2
#define sw3p 8  //3
#define swrp 7  //right
#define swlp 14 //left
#define swcp A2 //change

#define memAddr 0//eeprom address holding derailt room number

extern ClickButton btn_1(sw1p, LOW, HIGH);
extern ClickButton btn_2(sw2p, LOW, HIGH);
extern ClickButton btn_3(sw3p, LOW, HIGH);
extern ClickButton btn_L(swlp, LOW, HIGH);
extern ClickButton btn_R(swrp, LOW, HIGH);
extern ClickButton btn_C(swcp, LOW, HIGH);

extern byte currentReceiver = 0;

extern byte tmp = 0;

void changeReceiver() {
  tmp = currentReceiver;
  changeReceiverLed();
  while (1) {
    btn_1.Update(); btn_2.Update(); btn_3.Update(); btn_L.Update(); btn_C.Update();

    if (btn_1.quickPressed) {
      tmp++;
      tmp %= 7;
    }

    if (btn_3.quickPressed) {
      tmp--;
      if (tmp == 255)tmp = 6;
    }
    if (btn_2.quickPressed) {
      tmp = currentReceiver;
    }

    if (btn_C.quickPressed) {
      currentReceiver = tmp;
      EEPROM.write(memAddr, currentReceiver);
      finalDecision(currentReceiver + 1);
      offAllLeds();
      return;
    }

    showNum(tmp + 1);
    wdt_reset();
  }
}

