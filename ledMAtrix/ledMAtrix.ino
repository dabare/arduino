#include <LedControlMS.h>


LedControl lc=LedControl(16,14,15,1);

void setup() {
 lc.shutdown(0,false);
  lc.setIntensity(0,3);
    lc.clearDisplay(0);
   
}


void loop() {
  // put your main code here, to run repeatedly:
 lc.setLed(0,0,7,false);
 delay(100);
  lc.setLed(0,0,7,true);
  delay(100);
}
