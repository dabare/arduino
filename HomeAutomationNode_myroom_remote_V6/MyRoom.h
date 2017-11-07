#include "RFID.h"
#include "clickwheel.h"

#include <IRremote.h>

#define BTN_1 0x490
#define BTN_2 0xc90
#define BTN_3 0xa90
#define BTN_4 0x890
#define BTN_5 0x90
IRsend irsend;

void MyRoomFn() {
  data[0] = 1;
  if (btn_1.quickPressed) {
    data[1] = 2; //0read 1write 2invert
    data[2] = 0; //inverting switch no
    if (txrx()) {
      invert(0, data[2]);
    }
  }
  if (btn_2.quickPressed) {
    data[1] = 2; //0read 1write 2invert
    data[2] = 1; //inverting switch no
    if (txrx()) {
      invert(1, data[3]);
    }
  }
  if (btn_3.quickPressed) {
    data[1] = 2; //0read777 1write 2invert
    data[2] = 2; //inverting switch no
    if (txrx()) {
      invert(2, data[4]);
    }
  }
  if (btn_R.quickPressed) {
    data[1] = 1;//0read 1write 2invert
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    if (txrx()) {
      resetAll();
    }
  }
  if (btn_L.quickPressed) {
    data[1] = 0;//0read 1write 2invert
    if (txrx()) {
      showStat(data);
    }
  }

}

void TVFn() {
  if (btn_1.quickPressed || btn_1.longPress) {
    irsend.sendSony(BTN_1, 12); delay(20);
    irsend.sendSony(BTN_1, 12); delay(20);
  }
  if (btn_2.quickPressed || btn_2.longPress) {
    irsend.sendSony(BTN_2, 12); delay(20);
    irsend.sendSony(BTN_2, 12); delay(20);
  }
  if (btn_3.quickPressed) {
    irsend.sendSony(BTN_3, 12); delay(20);
    irsend.sendSony(BTN_3, 12); delay(20);
  }
  if (btn_L.quickPressed || btn_L.longPress) {
    irsend.sendSony(BTN_4, 12); delay(20);
    irsend.sendSony(BTN_4, 12); delay(20);
  }
  if (btn_R.quickPressed || btn_R.longPress) {
    irsend.sendSony(BTN_5, 12); delay(20);
    irsend.sendSony(BTN_5, 12); delay(20);
  }

  byte ccc = cliclWheelUpdate();
  if (ccc == 2) {
    irsend.sendSony(BTN_1, 12); delay(20);
    irsend.sendSony(BTN_1, 12); delay(20);
  } else if (ccc == 1) {
    irsend.sendSony(BTN_2, 12); delay(20);
    irsend.sendSony(BTN_2, 12); delay(20);
  }
}

void PCFn() {
  data[0] = 2;
  if (btn_1.quickPressed || btn_1.longPress) {
    data[1] = 1;
    tx_twobytes();
  }
  if (btn_2.quickPressed || btn_2.longPress) {
    data[1] = 2;
    tx_twobytes();
  }
  if (btn_3.quickPressed) {
    data[1] = 3;
    tx_twobytes();
  }
  if (btn_L.quickPressed || btn_L.longPress) {
    data[1] = 4;
    tx_twobytes();
  }
  if (btn_R.quickPressed || btn_R.longPress) {
    data[1] = 5;
    tx_twobytes();
  }

  byte ccc = cliclWheelUpdate();
  if (ccc == 1) {
    data[1] = 6;//c;
    tx_twobytes();
  } else if (ccc == 2) {
    data[1] = 7;//cc
    tx_twobytes();
  }
}


byte MyRoomRGB_selected_function = 0;
bool MyRoomRGB_R = 0, MyRoomRGB_G = 0, MyRoomRGB_B = 0;

void MyRoomRGBFn() {
  data[0] = 3;//id

  //change function
  if (btn_C.clicks == 1) {
    MyRoomRGB_selected_function = 0; //just light
  } else if (btn_C.clicks == 2) {
    offAllLeds();
    MyRoomRGB_selected_function = 1; //party
  }

  if (MyRoomRGB_selected_function) {//party
    if (btn_1.quickPressed) {
      data[1] = 1;
      data[1] = data[1] << 1;//shift left by 1 bit
      data[1] = data[1] << 1;
      data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)
      data[1] |= 0; //to denote main buttons(1,2,3), in left, right this will be 1
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    } else if (btn_2.quickPressed) {
      data[1] = 0;
      data[1] = data[1] << 1;//shift left by 1 bit
      data[1] |= 1;
      data[1] = data[1] << 1;
      data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)
      data[1] |= 0; //to denote main buttons(1,2,3), in left, right this will be 1
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    } else if (btn_3.quickPressed) {
      data[1] = 0;
      data[1] = data[1] << 1;//shift left by 1 bit
      data[1] = data[1] << 1;
      data[1] |= 1;
      data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)
      data[1] |= 0; //to denote main buttons(1,2,3), in left, right this will be 1
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    } else if (btn_L.quickPressed) {
      data[1] = 0;
      data[1] = data[1] << 1;//shift left by 1 bit
      data[1] = data[1] << 1;
      data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)
      data[1] |= 0; //to denote main buttons(1,2,3), in left, right this will be 1
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    } else if (btn_R.quickPressed) {
      data[1] = 0;
      data[1] = data[1] << 1;//shift left by 1 bit
      data[1] = data[1] << 1;
      data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)
      data[1] |= 0; //to denote main buttons(1,2,3), in left, right this will be 1
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    }
  } else {//light only
    data[1] = MyRoomRGB_R;
    data[1] = data[1] << 1;//shift left by 1 bit
    data[1] |= MyRoomRGB_G;
    data[1] = data[1] << 1;
    data[1] |= MyRoomRGB_B;
    data[1] = data[1] << 1;//shift left by 1 bit to pass increment(1) or decriment(0)

    if (btn_1.quickPressed) {
      MyRoomRGB_R = !MyRoomRGB_R;
    }
    if (btn_2.quickPressed) {
      MyRoomRGB_G = !MyRoomRGB_G;
    }
    if (btn_3.quickPressed) {
      MyRoomRGB_B = !MyRoomRGB_B;
    }
    setLeds(MyRoomRGB_R, MyRoomRGB_G, MyRoomRGB_B);
    if (btn_L.quickPressed || btn_L.longPress) {
      data[1] |= 0; //decrimet
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    } else if (btn_R.quickPressed || btn_R.longPress) {
      data[1] |= 1; //incrimet
      data[1] = data[1] << 1;//shift left by 1 bit to pass function(just light(0) or party(1))
      data[1] |= MyRoomRGB_selected_function;
      tx_twobytes();
    }
  }
}


bool CarFn_F, CarFn_B, CarFn_L, CarFn_R;
byte CarFn_offsig = 10, CarFn_old_sig = 0;
void CarFn() {
  data[0] = 5;
  //data[1] = 253;
  data[1] = btn_R.btnState;//1
  data[1] = data[1] << 1;
  data[1] |= btn_L.btnState; //2
  data[1] = data[1] << 1;
  data[1] |= btn_1.btnState; //3
  data[1] = data[1] << 1;
  data[1] |= btn_2.btnState; //4
  data[1] = data[1] << 4;


  if (data[1] != CarFn_old_sig) {
    CarFn_offsig = 10;
  }
  if (CarFn_offsig) {
    tx_twobytes();
    CarFn_offsig--;
  }
  CarFn_old_sig = data[1];
}
