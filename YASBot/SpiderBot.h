#pragma once

#include "Leg.h"

class SpiderBot {
  public:
    SpiderBot(Adafruit_PWMServoDriver* driver);

    //move all legs to the same position
    void allLegs(float root, float arm, float wrist);

    //simple configurations
    void conf_stand();
    void conf_crouch();

    void tick();
    void finishMoving(); //wait until all legs have moved to their target locations

    bool targetsReached();

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