#include "Keyboard.h"

void setup() {
  Keyboard.begin();
  Serial.begin(115200);
}

void loop() {
    Keyboard.press(219);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.press(219);
    Keyboard.releaseAll();

    
    Keyboard.press(193);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.press(193);
    Keyboard.releaseAll();
    
    Keyboard.press(207);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.press(207);
    Keyboard.releaseAll();
}


