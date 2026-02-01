#pragma once

#include "Leg.h"

class SpiderBot {
  public:
    SpiderBot(Adafruit_PWMServoDriver* driver);

    //settings (sets values for all legs)
    void setUsePIs(bool rootu, bool armu, bool wristu);
    void setUseSlews(bool rootu, bool armu, bool wristu);
    void setSpeeds(float roots, float arms, float wrists);

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