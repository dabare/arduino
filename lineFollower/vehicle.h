#include <LedControlMS.h>
#include "Motor.h"
#include "sensorPanel.h"
#include "path.h"
//-================================motors====================
#define MLF 9
#define MLB 10
#define MRF 5
#define MRB 6

//================================sensors===================



//===========================matrix===================
#define CLK 14
#define CS 15
#define DIN 16
#define delaytime 10

class vehicle {
  private:
    Motor* leftMotor ;
    Motor* rightMotor ;
    sensorPanel* sensor ;
    LedControl* lc;

    byte JL = 11;
    byte JR = 2;
    byte PR = 3;
    byte PL = 4;
    byte JF = 12;
    byte JY = 13;
    byte PK = 7;

    bool logo[16][8]={
      {1,1,0,1,0,0,0,1},
      {1,0,1,1,0,1,1,0},
      {0,1,1,1,1,0,0,0},
      {0,0,1,0,1,1,1,0},
      {0,0,1,0,1,0,1,1},
      {1,1,0,1,0,0,0,0},
      {1,1,1,0,1,1,1,1},
      {}
      };

  public:
    vehicle();
    void followLine();
    void stop();
    void turnRight();
    void turnLeft();
    void forward();
    void reverse();
    void quickRight();
    void quickLeft();
    void drawSensors();
    bool isABC();
    bool isA();
    bool isAB();
    bool isBC();
    bool isC();
    bool isAC();
    bool isJun();
    void updateSensors();
    void displayLogo();
    void solveMesh();

};

vehicle::vehicle() {
  leftMotor = new Motor(MLF, MLB);
  rightMotor = new Motor(MRF, MRB);
  sensor = new sensorPanel(new Sensor(JL), new Sensor(JR), new Sensor(PR), new Sensor(PL), new Sensor(JF), new Sensor(JY), new Sensor(PK));
  lc = new LedControl(DIN, CLK, CS, 1);
  lc->shutdown(0, false);
  lc->setIntensity(0, 2);
  lc->clearDisplay(0);
  displayLogo();
};


void vehicle::followLine() {
  sensor->updateSensors();
  //drawSensors();
  if (sensor->VJF && !sensor->VJL && sensor->VJR) {
    while (sensor->JF->isOn()) {
      quickLeft();
    }
    stop();
  } else if (sensor->VJF && sensor->VJL && !sensor->VJR) {
    while (sensor->JF->isOn()) {
      quickRight();
    }
    stop();
  }
  else if (!sensor->VPL && sensor->VPR) {
    turnLeft();
  } else if (sensor->VPL && !sensor->VPR) {
    turnRight();
  } else if (!sensor->VPL && !sensor->VPR) {
    forward();
  } else {
    stop();
  }
};
void vehicle::stop() {
  leftMotor->stop();
  rightMotor->stop();
};
void vehicle::turnRight() {
  leftMotor->forward();
  rightMotor->stop();
};
void vehicle::turnLeft() {
  leftMotor->stop();
  rightMotor->forward();
};
void vehicle::forward() {
  leftMotor->forward();
  rightMotor->forward();
};
void vehicle::reverse() {
  leftMotor->backward();
  rightMotor->backward();
};
void vehicle::quickRight() {
  leftMotor->forward();
  rightMotor->backward();
};
void vehicle::quickLeft() {
  leftMotor->backward();
  rightMotor->forward();
};
void vehicle::drawSensors() {
  if (sensor->VJL) {
    lc->setLed(0, 0, 2, false);
    //lc->setLed(0, 0, 3, false);
    //lc->setLed(0, 1, 2, false);
    //lc->setLed(0, 1, 3, false);
  } else {
    lc->setLed(0, 0, 2, true);
    //lc->setLed(0, 0, 3, true);
    //lc->setLed(0, 1, 2, true);
    //lc->setLed(0, 1, 3, true);
  }

  if (sensor->VPL) {
    lc->setLed(0, 2, 2, false);
    //lc->setLed(0, 2, 3, false);
    //lc->setLed(0, 3, 2, false);
    //lc->setLed(0, 3, 3, false);
  } else {
    lc->setLed(0, 2, 2, true);
    //lc->setLed(0, 2, 3, true);
    //lc->setLed(0, 3, 2, true);
    //lc->setLed(0, 3, 3, true);
  }

  if (sensor->VPR) {
    lc->setLed(0, 4, 2, false);
    //lc->setLed(0, 4, 3, false);
    //lc->setLed(0, 5, 2, false);
    //lc->setLed(0, 5, 3, false);
  } else {
    lc->setLed(0, 4, 2, true);
    //lc->setLed(0, 4, 3, true);
    //lc->setLed(0, 5, 2, true);
    //lc->setLed(0, 5, 3, true);
  }

  if (sensor->VJR) {
    lc->setLed(0, 6, 2, false);
    //lc->setLed(0, 6, 3, false);
    //lc->setLed(0, 7, 2, false);
    //lc->setLed(0, 7, 3, false);
  } else {
    lc->setLed(0, 6, 2, true);
    //lc->setLed(0, 6, 3, true);
    //lc->setLed(0, 7, 2, true);
    //lc->setLed(0, 7, 3, true);
  }

  if (sensor->VJF) {
    lc->setLed(0, 3, 5, false);
    //lc->setLed(0, 3, 6, false);
    //lc->setLed(0, 4, 5, false);
    //lc->setLed(0, 4, 6, false);
  } else {
    lc->setLed(0, 3, 5, true);
    //lc->setLed(0, 3, 6, true);
    //lc->setLed(0, 4, 5, true);
    //lc->setLed(0, 4, 6, true);
  }

  if (sensor->VJY) {
    lc->setLed(0, 0, 5, false);
    //lc->setLed(0, 0, 6, false);
    //lc->setLed(0, 1, 5, false);
    //lc->setLed(0, 1, 6, false);
  } else {
    lc->setLed(0, 0, 5, true);
    //lc->setLed(0, 0, 6, true);
    //lc->setLed(0, 1, 5, true);
    //lc->setLed(0, 1, 6, true);
  }

  if (sensor->VPK) {
    lc->setLed(0, 7, 0, false);
  } else {
    lc->setLed(0, 7, 0, true);
  }
};
bool vehicle::isABC() {
  return !sensor->VJL && !sensor->VJR && !sensor->VPL && !sensor->VPR && !sensor->VJF;
};
bool vehicle::isA() {
  return sensor->VJL && sensor->VPL && sensor->VPR ;
};
bool vehicle::isAB() {
  return !sensor->VJL && sensor->VJR && !sensor->VPL && !sensor->VPR && !sensor->VJF;
};
bool vehicle::isBC() {
  return sensor->VJL && !sensor->VJR && !sensor->VPL && !sensor->VPR && !sensor->VJF;
};
bool vehicle::isC() {
  return sensor->VJR && sensor->VPL && sensor->VPR ;
};
bool vehicle::isAC() {
  return !sensor->VJL && !sensor->VJR && !sensor->VPL && !sensor->VPR && sensor->VJF;
};
bool vehicle::isJun() {
  sensor->updateSensors();
  return isABC() || isAB() || isBC() || isAC();
};
inline void vehicle::updateSensors() {
  sensor->updateSensors();
};
void vehicle::displayLogo() {
  for (int t = 0; t < 8; t++) {
    for (int row = 0; row < 8; row++) {
      lc->setRow(0, row, logo[t][row]);
    }
    delay(100);
    
  }
};
void vehicle::solveMesh() {
  sensor->updateSensors();
  while (!isJun()) {
    followLine();
  }
  stop();
};
