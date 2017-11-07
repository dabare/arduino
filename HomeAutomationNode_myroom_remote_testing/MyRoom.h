#include "globals.h"

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
    data[1] = 2; //0read 1write 2invert
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
  if (btn_L.clicks == 1) {
    data[1] = 0;//0read 1write 2invert
    if (txrx()) {
      showStat(data);
    }
  }

}

void VLCFn() {
  data[0] = 2;
  if (btn_1.quickPressed || btn_1.longPress == -1) {
    data[1] = 1;
    tx_twobyte();
  }
  if (btn_2.quickPressed || btn_2.longPress == -1) {
    data[1] = 2;
    tx_twobyte();
  }
  if (btn_3.quickPressed || btn_3.longPress == -1) {
    data[1] = 3;
    tx_twobyte();
  }
  if (btn_R.quickPressed || btn_R.longPress == -1) {
    data[1] = 4;
    tx_twobyte();
  }
  if (btn_L.quickPressed) {
    data[1] = 5;
    tx_twobyte();
  }
}

