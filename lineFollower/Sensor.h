#include <arduino.h>

#define blackPath 1
#define senorLightDelay 200
#define sensorPin 8

class Sensor {
  private:
    byte pin;
    bool stat;
  public:
    Sensor(byte p);
    bool isOn();
};
Sensor::Sensor(byte p) {
  pin = p;
  pinMode(p , OUTPUT);
  pinMode(sensorPin,INPUT);
  digitalWrite(p , HIGH);
}

inline bool Sensor::isOn() {
  stat = false;
  digitalWrite(pin, LOW);
  delayMicroseconds(senorLightDelay);
  stat = digitalRead(sensorPin);
  digitalWrite(pin, HIGH);
  if (blackPath) {
    return blackPath - stat;
  } else {
    return stat;
  }
}
