#include "Sensor.h"

class sensorPanel {
  private:


  public:
    Sensor* JL;
    Sensor* JR;
    Sensor* PR;
    Sensor* PL;
    Sensor* JF;
    Sensor* JY;
    Sensor* PK;

    bool VJL=0;
    bool VPL;
    bool VPR;
    bool VJR;
    bool VJF;
    bool VJY;
    bool VPK;
    byte val;


    sensorPanel(Sensor* PJL, Sensor* PJR, Sensor* PPR, Sensor* PPL, Sensor* PJF, Sensor* PJY , Sensor* PPK);
    void updateSensors();
    byte getJunctionVal();
};

sensorPanel::sensorPanel(Sensor* PJL, Sensor* PJR, Sensor* PPR, Sensor* PPL, Sensor* PJF, Sensor* PJY , Sensor* PPK) {
  JL = PJL;
  JR = PJR;
  PR = PPR;
  PL = PPL;
  JF = PJF;
  JY = PJY;
  PK = PPK;

  val = 0;
};
void sensorPanel::updateSensors() {
  VJL = JL->isOn();
  VPL = PL->isOn();
  VPR = PR->isOn();
  VJR = JR->isOn();
  VJF = JF->isOn();
  VJY = JY->isOn();
  VPK = PK->isOn();
};
inline byte sensorPanel::getJunctionVal() {
  return VJL + 2 * VPL + 4 * VPR + 8 * VJR + 16 * VJF + 32 * VJY + 64 * VPK;
};

