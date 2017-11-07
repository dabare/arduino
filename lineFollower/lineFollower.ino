#include "vehicle.h"

vehicle* v;

void setup() {
  Serial.begin(9600);
  v = new vehicle();
}

void loop() {
  v->displayLogo();
}


