#include "Receiver.h"

Receiver::Receiver(callbackFunction newFunction) {
  _callbackFunction = newFunction;
}

void Receiver::Update() {
  if (_callbackFunction) _callbackFunction();
}


void Receiver::attachFunction(callbackFunction newFunction) {
  _callbackFunction = newFunction;
}
