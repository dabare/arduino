#include <MFRC522.h>
#include <SPI.h>
#include "globals.h"


#define RST_PIN         0          // Configurable, see typical pin layout above
#define SS_PIN          1         // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void initRFID() {
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
}

void checkRFID() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    currentReceiver = 0;
    EEPROM.write(memAddr, currentReceiver);
    finalDecision(currentReceiver + 1);
  }
}
