#include "Leg.h"

Leg::Leg() {
  root = Motor();
  arm = Motor();
  wrist = Motor();
}

Leg::Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid) {
  root = Motor(rid, driver);
  arm = Motor(aid, driver);
  wrist = Motor(wid, driver);
}

Leg::Leg(Adafruit_PWMServoDriver* driver, uint8_t rid, uint8_t aid, uint8_t wid, limit_s rootl, limit_s arml, limit_s wristl) {
  root = Motor(rid, driver, rootl);
  arm = Motor(aid, driver, arml);
  wrist = Motor(wid, driver, wristl);
}

void Leg::setPositions(float rootp, float armp, float wristp) {
  root.setTarget(rootp);
  arm.setTarget(armp);
  wrist.setTarget(wristp);
}

void Leg::tick() {
  root.tick();
  arm.tick();
  wrist.tick();
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
