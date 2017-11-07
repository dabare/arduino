
#include <avr/wdt.h>
#include "RF24.h"
#include <EEPROM.h>

#define id 3

#define rp 5
#define gp 6
#define bp 3

#define rMemAddr 0
#define gMemAddr 1
#define bMemAddr 2

RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.

byte signalRead[2] = {0, 0}; //id,val
byte r = 0, g = 0, b = 0, sig;
void setup() {
  Serial.begin(115200);
  pinMode(rp, OUTPUT); pinMode(gp, OUTPUT); pinMode(bp, OUTPUT);

  radio.begin();
  radio.setAutoAck(false);

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  radio.startListening();
  Serial.begin(115200);
  r = EEPROM.read(rMemAddr); g = EEPROM.read(gMemAddr); b = EEPROM.read(bMemAddr);

  digitalWrite(bp, 1);
  delay(150);
  digitalWrite(bp, 0);
  watchdogSetup();

}

bool sig_r = 0, sig_g = 0, sig_b = 0, sig_inc, sig_fun, flash = 0, smooth = 0, randm = 0, randmFlash = 0;
void loop() {
  wdt_reset();
  checkSig();

  if (sig_fun) { //party
    if (flash) {
      fastFlash();
    } else if (smooth) {
      smoothChange();
    } else if (randm) {
      //randomCol();
      RandomFastFlash();
    } else if (randmFlash) {
      RandomFastFlash();
    }
  }
}
int randomCol_speed_increment = 0;
void randomCol() {
  if (randomCol_speed_increment % 10000 == 0) {
    analogWrite(rp, random(0, r)); analogWrite(gp, random(0, g)); analogWrite(bp, random(0, b));
  }
  randomCol_speed_increment++;
}

void fastFlash() {
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
  delay(5);
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(150);
}
void RandomFastFlash() {
  analogWrite(rp, random(0, r)); analogWrite(gp, random(0, g)); analogWrite(bp, random(0, b));
  delay(5);
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(150);
}

byte smooth_lights[] {0, 0, 0};
byte smooth_inc_l = random(1, 8);
byte smooth_l = 0;
byte temp;
int smooth_speed_increment = 0;

void smoothChange() {
  if (smooth_speed_increment % 7000 == 0) {
    temp = smooth_inc_l;
    if (temp / 4) {
      if (smooth_lights[0] != r) smooth_lights[0]++;
    } else {
      if (smooth_lights[0] != 0) smooth_lights[0]--;
    }
    temp %= 4;
    if (temp / 2) {
      if (smooth_lights[1] != g) smooth_lights[1]++;
    } else {
      if (smooth_lights[1] != 0) smooth_lights[1]--;
    }
    temp %= 2;
    if (temp) {
      if (smooth_lights[2] != b) smooth_lights[2]++;
    } else {
      if (smooth_lights[2] != 0) smooth_lights[2]--;
    }

    analogWrite(rp, smooth_lights[0]); analogWrite(gp, smooth_lights[1]); analogWrite(bp, smooth_lights[2]);
    if ((smooth_lights[0] == r && r) || (smooth_lights[1] == g && g) || ( smooth_lights[2] == b && b)) {
      //smooth_inc_l = random(1, 8);
      smooth_inc_l %= 7;
      smooth_inc_l++;
    }
  }
  smooth_speed_increment++;
}

void checkSig() {
  if ( radio.available() ) {
    while (radio.available()) {
      radio.read( &signalRead, 2 );
    }
    if (signalRead[0] == id) {
      sig = signalRead[1];
      sig_r = sig / 16;
      sig %= 16;

      sig_g = sig / 8;
      sig %= 8;

      sig_b = sig / 4;
      sig %= 4;

      sig_inc = sig / 2;
      sig %= 2;

      sig_fun = sig;

      if (sig_fun) { //party
        if (sig_r) {
          flash = 1;
          smooth = 0;
          randm = 0;
        }
        if (sig_g) {
          smooth = 1;
          flash = 0;
          randm = 0;
          smooth_lights[0] = 0; smooth_lights[1] = 0; smooth_lights[2] = 0;
        }
        if (sig_b) {
          smooth = 0;
          flash = 0;
          randm = 1;
        }
      } else { //only light
        if (sig_inc) {
          switch (sig_r * 100 + sig_g * 10 + sig_b) {
            case 1:
              if ( b == 255) {
                reachedMAX();
              } else {
                b++;
              }
              break;
            case 10:
              if ( g == 255 ) {
                reachedMAX();
              } else {
                g++;
              }
              break;
            case 11:
              if ( g == 255 || b == 255) {
                reachedMAX();
              } else {
                g++; b++;
              }
              break;
            case 100:
              if (r == 255) {
                reachedMAX();
              } else {
                r++;
              }
              break;
            case 101:
              if (r == 255  || b == 255) {
                reachedMAX();
              } else {
                r++; b++;
              }
              break;
            case 110:
              if (r == 255 || g == 255 ) {
                reachedMAX();
              } else {
                r++; g++;
              }
              break;
            case 111:
              if (r == 255 || g == 255 || b == 255) {
                reachedMAX();
              } else {
                r++; g++; b++;
              }
              break;
          }
        } else {
          switch (sig_r * 100 + sig_g * 10 + sig_b) {
            case 1:
              if ( b == 0) {
                reachedMAX();
              } else {
                b--;
              }
              break;
            case 10:
              if ( g == 0 ) {
                reachedMAX();
              } else {
                g--;
              }
              break;
            case 11:
              if ( g == 0 || b == 0) {
                reachedMAX();
              } else {
                g--; b--;
              }
              break;
            case 100:
              if (r == 0) {
                reachedMAX();
              } else {
                r--;
              }
              break;
            case 101:
              if (r == 0  || b == 0) {
                reachedMAX();
              } else {
                r--; b--;
              }
              break;
            case 110:
              if (r == 0 || g == 0 ) {
                reachedMAX();
              } else {
                r--; g--;
              }
              break;
            case 111:
              if (r == 0 || g == 0 || b == 0) {
                reachedMAX();
              } else {
                r--; g--; b--;
              }
              break;
          }
        }
        EEPROM.write(rMemAddr, r); EEPROM.write(gMemAddr, g); EEPROM.write(bMemAddr, b);
        analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
      }
    }
  }
}

void reachedMAX() {
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
  delay(100);
  wdt_reset();
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(100);
  wdt_reset();
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
  delay(100);
  wdt_reset();
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
  delay(100);
  wdt_reset();
  analogWrite(rp, r); analogWrite(gp, g); analogWrite(bp, b);
  delay(100);
  wdt_reset();
  analogWrite(rp, 0); analogWrite(gp, 0); analogWrite(bp, 0);
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
