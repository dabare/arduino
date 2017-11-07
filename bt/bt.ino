#include <SoftwareSerial.h>
#define rate 9600
SoftwareSerial BTSerial(8, 7); //TX,RX

void setup() {

  // put your setup code here, to run once:
  Serial.begin(rate);
  Serial.println("enter at command");
  BTSerial.begin(rate);
   BTSerial.write("AT+VERSION?\r\n");
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
    BTSerial.write(Serial.read());
  if (BTSerial.available())
    Serial.write(BTSerial.read());
}
