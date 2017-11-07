// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"

const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentExtended      display(PIN_CLK, PIN_DIO);

RTC_DS3231 rtc;

void setup () {
  display.begin();            // initializes the display
  display.setBacklight(20);  
  //rtc.adjust(DateTime(2017, 3, 13, 22, 30, 0));
}

void loop () {
  
    DateTime now = rtc.now();
     byte hours    = now.hour();     
     hours%=12;// initialize hours
     byte minutes  = now.minute();                           
    display.printTime(hours, minutes, true);
    delay(1000);
}
