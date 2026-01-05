#pragma once

#include "Motor.h"

class Leg {
  public:
    Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid);
    Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, limit_s rootl, limit_s arml, limit_s wristl);

    void setPositions(float rootp, float armp, float wristp);

    void tick();

    Motor* getRoot();
    Motor* getArm();
    Motor* getWrist();

  private:
    Motor root;
    Motor arm;
    Motor wrist;
};