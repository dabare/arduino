#include "Arduino.h"
#include "clickButton.h"


extern "C" {
  typedef void (*callbackFunction)(void);
}

class Receiver
{
  public:
    Receiver::Receiver(callbackFunction newFunction);
    
    void Update();
    void attachFunction(callbackFunction newFunction);
    
  private:
    callbackFunction _callbackFunction;
};
