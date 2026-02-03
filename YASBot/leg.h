#pragma once

#include "motor.h"

typedef struct {
  float root, arm, wrist;
} LEG_CONFIG;

class Leg {
  public:
    Leg();
    Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, bool root_reversed);
    Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, bool root_reversed, limit_s rootl, limit_s arml, limit_s wristl);

    void setPositions(float rootp, float armp, float wristp);
    void setConfig(LEG_CONFIG conf);
    void setUsePIs(bool rootu, bool armu, bool wristu);
    void setUseSlews(bool rootu, bool armu, bool wristu);
    void setSpeeds(float roots, float arms, float wrists);

    void tick();
    void finishMoving(); //wait until all motors have reached their target positions

    bool targetsReached();

    //basic animations and movements
    void simple_walk_cycle(float anim); //walk cycle with anim controlling what part of the cycle to move to

    Motor* getRoot();
    Motor* getArm();
    Motor* getWrist();

  private:
    Motor root;
    Motor arm;
    Motor wrist;
};