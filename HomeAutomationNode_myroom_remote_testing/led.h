#include <Arduino.h>
#include <avr/wdt.h>


#define led1 3
#define led2 5
#define led3 6
#define ledsig 19
#define ledMaxPow 10
#define ledMinPow 0

#define loopDelay 5
#define checkDelay 10

byte leds[] = {led1, led2, led3};

void initLeds() {
  pinMode(led1, OUTPUT); pinMode(led2, OUTPUT); pinMode(led3, OUTPUT); pinMode(ledsig, OUTPUT);

  pinMode(18, OUTPUT);//ledsig negative pin
  digitalWrite(18, 0);

  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led3, i);
    delay(loopDelay);
  }
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led2, i);
    delay(loopDelay);
  }
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led1, i);
    delay(loopDelay);
  }

  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led3, i);
    delay(loopDelay);
  }
  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led2, i);
    delay(loopDelay);
  }
  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led1, i);
    delay(loopDelay);
  }
}

void invert(byte led, boolean val) {
  if (val) {
    analogWrite(leds[led], ledMaxPow);
    delay(50);
    analogWrite(leds[led], ledMinPow);
    delay(50);

    analogWrite(leds[led], ledMaxPow);
    delay(50);
    analogWrite(leds[led], ledMinPow);
  } else {
    analogWrite(leds[led], ledMaxPow);
    delay(150);
    analogWrite(leds[led], ledMinPow);
  }
}

void resetAll() {
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led3, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led2, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led1, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led1, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led2, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMaxPow; i >= ledMinPow; i--) {
    analogWrite(led3, i);
    delay(checkDelay);
  }
}


void showStat(byte data[]) {
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led3, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led2, i);
    delay(checkDelay);
  }
  wdt_reset();
  for (int i = ledMinPow; i <= ledMaxPow; i++) {
    analogWrite(led1, i);
    delay(checkDelay);
  }

  if (data[2] || data[3] || data[4]) {
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led1, i); analogWrite(led2, i); analogWrite(led3, i);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMinPow; i <= ledMaxPow; i++) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMinPow; i <= ledMaxPow; i++) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMinPow; i <= ledMaxPow; i++) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led1, i * data[2]); analogWrite(led2, i * data[3]); analogWrite(led3, i * data[4]);
      delay(checkDelay);
    }
  } else {
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led1, i);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led2, i);
      delay(checkDelay);
    }
    wdt_reset();
    for (int i = ledMaxPow; i >= ledMinPow; i--) {
      analogWrite(led3, i);
      delay(checkDelay);
    }
  }
}

void changeReceiverLed() {
  analogWrite(led1, ledMaxPow); analogWrite(led2, ledMaxPow); analogWrite(led3, ledMaxPow);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
  delay(50);

  analogWrite(led1, ledMaxPow); analogWrite(led2, ledMaxPow); analogWrite(led3, ledMaxPow);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
  delay(50);

  analogWrite(led1, ledMaxPow); analogWrite(led2, ledMaxPow); analogWrite(led3, ledMaxPow);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
}

void showNum(byte num) {
  analogWrite(led1, (num / 4)*ledMaxPow);
  num %= 4;
  analogWrite(led2, (num / 2)*ledMaxPow);
  num %= 2;
  analogWrite(led3, num * ledMaxPow);
}

void finalDecision(byte num) {
  showNum(num);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
  delay(50);

  showNum(num);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
  delay(50);

  showNum(num);
  delay(50);
  analogWrite(led1, 0); analogWrite(led2, 0); analogWrite(led3, 0);
}
