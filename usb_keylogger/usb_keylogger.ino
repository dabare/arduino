#include <hidboot.h>
#include <usbhub.h>
#include "Keyboard.h"
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

class KbdRptParser : public KeyboardReportParser
{
  public:
    byte keyVals[60]={};
    KbdRptParser();
  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
};
KbdRptParser::KbdRptParser(void){
  /*
    case 42:    // backspace`
    case 43:    // tab`
    case 40:    // enter`
    case 73:    // insert`
    case 76:    // delete`
    case 74:    // home`
    case 77:    // end`
    case 75:    // pageup`
    case 78:    // pagedown`
    case 80:    // left`
    case 82:    // up`
    case 81:    // down`
    case 79:    // right`
    case 95:    // kp-7 home`
    case 92:    // KP-4 / Left`
    case 89:    // KP-1 / End`
    case 96:    // KP-8 / Up`
    case 90:    // KP-2 / Down`
    case 98:    // KP-0 / Ins`
    case 97:    // KP-9 / PgUp`
    case 94:    // KP-6 / Right`
    case 91:    // KP-3 / PgDn`
    case 99:    // KP-. / Del`
    case 41:    //esc`
    case 70:    //printscreen
    58-69-   fa-f12`
  **/
  keyVals[42]=KEY_UP_ARROW;
  keyVals[56]=KEY_UP_ARROW;
  keyVals[41]=KEY_DOWN_ARROW;
  keyVals[50]=KEY_DOWN_ARROW;
  keyVals[40]=KEY_LEFT_ARROW;
  keyVals[52]=KEY_LEFT_ARROW;
  keyVals[39]=KEY_RIGHT_ARROW;
  keyVals[54]=KEY_RIGHT_ARROW;
  keyVals[2]=KEY_BACKSPACE;
  keyVals[3]=KEY_TAB;
  keyVals[0]=KEY_RETURN;
  keyVals[48]=KEY_RETURN;
  keyVals[1]=KEY_ESC;
  keyVals[33]=KEY_INSERT;
  keyVals[58]=KEY_INSERT;
  keyVals[59]=KEY_DELETE;
  keyVals[36]=KEY_DELETE;
  keyVals[57]=KEY_PAGE_UP;
  keyVals[35]=KEY_PAGE_UP;
  keyVals[51]=KEY_PAGE_DOWN;
  keyVals[38]=KEY_PAGE_DOWN;
  keyVals[55]=KEY_HOME;
  keyVals[34]=KEY_HOME;
  keyVals[49]=KEY_END;
  keyVals[37]=KEY_END;
  keyVals[18]=KEY_F1;
  keyVals[19]=KEY_F2;
  keyVals[20]=KEY_F3;
  keyVals[21]=KEY_F4;
  keyVals[22]=KEY_F5;
  keyVals[23]=KEY_F6;
  keyVals[24]=KEY_F7;
  keyVals[25]=KEY_F8;
  keyVals[26]=KEY_F9;
  keyVals[27]=KEY_F10;
  keyVals[28]=KEY_F11;
  keyVals[29]=KEY_F12;
}

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  digitalWrite(13,1);
  //Serial.print("DN ");
  uint8_t c = OemToAscii(mod, key);
  //Serial1.println(key);
  if(c==19){
    c=0;  
  }
  if (c){
    Keyboard.press(c);
      Serial1.print((char)c);
  }else{
    Keyboard.press(keyVals[key-40]);
    switch(keyVals[key-40]){
      case KEY_RETURN:
        Serial1.print(" [ENTR]<br>");
        break;
      case KEY_ESC:
        Serial1.print(" [esc]<br>");
        break;
      case KEY_UP_ARROW:
        Serial1.print(" [up]");
        break;
      case KEY_DOWN_ARROW:
        Serial1.print(" [down]");
        break;
      case KEY_LEFT_ARROW:
        Serial1.print(" [left]");
        break;
      case KEY_RIGHT_ARROW:
        Serial1.print(" [right]");
        break;
      case KEY_BACKSPACE:
        Serial1.print(" [b_spc]");
        break;
      case KEY_TAB:
        Serial1.print(" [tab]");
        break;
      case KEY_DELETE:
        Serial1.print(" [delete]");
        break;
      default:
        Serial1.print("<br>");
    }
  }
  digitalWrite(13,0);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {
  digitalWrite(13,1);
  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    if(afterMod.bmLeftCtrl){
      Keyboard.press(KEY_LEFT_CTRL);
      Serial1.print(" [CTRL]");
    }else{
      Keyboard.release(KEY_LEFT_CTRL);
    }
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    if(afterMod.bmLeftShift){
      Keyboard.press(KEY_LEFT_SHIFT);
    }else{
      Keyboard.release(KEY_LEFT_SHIFT);
    }
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    if(afterMod.bmLeftAlt){
      Keyboard.press(KEY_LEFT_ALT);
      Serial1.print(" [ALT]");
    }else{
      Keyboard.release(KEY_LEFT_ALT);
    }
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    if(afterMod.bmLeftGUI){
      Keyboard.press(KEY_LEFT_GUI);
      Serial1.print(" [GUI]");
    }else{
      Keyboard.release(KEY_LEFT_GUI);
    }
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    if(afterMod.bmRightCtrl){
      Keyboard.press(KEY_RIGHT_CTRL);
      Serial1.print(" [CTRL]");
    }else{
      Keyboard.release(KEY_RIGHT_CTRL);
    }
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    if(afterMod.bmRightShift){
      Keyboard.press(KEY_RIGHT_SHIFT);
    }else{
      Keyboard.release(KEY_RIGHT_SHIFT);
    }
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    if(afterMod.bmRightAlt){
      Keyboard.press(KEY_RIGHT_ALT);
      Serial1.print(" [ALT]");
    }else{
      Keyboard.release(KEY_RIGHT_ALT);
    }
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    if(afterMod.bmRightGUI){
      Keyboard.press(KEY_RIGHT_GUI);
      Serial1.print(" [GUI]");
    }else{
      Keyboard.release(KEY_RIGHT_GUI);
    }
  }
  digitalWrite(13,0);
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  digitalWrite(13,1);
  //Serial.print("UP ");
  uint8_t c = OemToAscii(mod, key);
  if(c==19){
    c=0;  
  }
  if (c){
    Keyboard.release(c);
  }else{
    Keyboard.release(keyVals[key-40]);
  }
  digitalWrite(13,0);
}

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

uint32_t next_time;

KbdRptParser Prs;

void setup()
{
  Keyboard.begin();
  delay(1000);
  pinMode(13,OUTPUT);
  Serial1.begin( 115200 );
  Serial.begin( 115200 );
//#if !defined(__MIPSEL__)
  //while (!Serial1); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
//#endif
  Serial1.println("Start");

  if (Usb.Init() == -1)
    Serial1.println("OSC did not start.");

  delay( 200 );

  next_time = millis() + 5000;

  HidKeyboard.SetReportParser(0, &Prs);
  
}

void loop()
{
  //Serial.println("loop");
  Usb.Task();
}

