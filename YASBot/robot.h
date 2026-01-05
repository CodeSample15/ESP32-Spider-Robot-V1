#pragma once

#include "Leg.h"

class Robot {
  public:
    Robot(Adafruit_PWMServoDriver* driver);

    //move all legs to the same position
    void allLegs(float root, float arm, float wrist);

    //simple configurations
    void conf_stand();
    void conf_crouch();

    void tick();

    Leg* getBackRight();
    Leg* getBackLeft();
    Leg* getFrontLeft();
    Leg* getFrontRight();

  private:
    Leg backRight;
    Leg backLeft;
    Leg frontLeft;
    Leg frontRight;
};