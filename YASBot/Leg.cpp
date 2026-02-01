#include "leg.h"

Leg::Leg() {
  root = Motor();
  arm = Motor();
  wrist = Motor();
}

Leg::Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, bool root_reversed) {
  root = Motor(rid, driver, root_reversed);
  arm = Motor(aid, driver, false);
  wrist = Motor(wid, driver, false);
}

Leg::Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, bool root_reversed, limit_s rootl, limit_s arml, limit_s wristl) {
  root = Motor(rid, driver, root_reversed, rootl);
  arm = Motor(aid, driver, false, arml);
  wrist = Motor(wid, driver, false, wristl);
}

void Leg::setPositions(float rootp, float armp, float wristp) {
  root.setTarget(rootp);
  arm.setTarget(armp);
  wrist.setTarget(wristp);
}

void Leg::setUsePIs(bool rootu, bool armu, bool wristu) {
  root.setUsePI(rootu);
  arm.setUsePI(armu);
  wrist.setUsePI(wristu);
}

void Leg::setUseSlews(bool rootu, bool armu, bool wristu) {
  root.setUseSlew(rootu);
  arm.setUseSlew(armu);
  wrist.setUseSlew(wristu);
}

void Leg::setSpeeds(float roots, float arms, float wrists) {
  root.setSpeed(roots);
  arm.setSpeed(arms);
  wrist.setSpeed(wrists);
}

void Leg::tick() {
  root.tick();
  arm.tick();
  wrist.tick();
}

void Leg::finishMoving() {
  while(!targetsReached())
    tick(); //just keep ticking until all motors have reached their destination
}

bool Leg::targetsReached() {
  return root.targetReached() && arm.targetReached() && wrist.targetReached();
}

void Leg::simple_walk_cycle(float anim) {
  float anims = sin(anim); //constrain anim progress between -1 and 1
  float animc = cos(anim);

  root.setTarget(-0.5 + (anims * 0.4));
  arm.setTarget(0.3 + (animc * 0.4));
  wrist.setTarget(-0.1);
}

Motor* Leg::getRoot() {
  return &root;
}

Motor* Leg::getArm() {
  return &arm;
}

Motor* Leg::getWrist() {
  return &wrist;
}
