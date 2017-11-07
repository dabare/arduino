#include <IRremote.h>

IRsend irsend;

void setup() {
}

void loop() {
    irsend.sendSony(0x68B92, 2);
    delay(100);
    irsend.sendSony(0x68B92, 2);
    delay(100);
    irsend.sendSony(0x68B92, 2);
    delay(1000);
}
