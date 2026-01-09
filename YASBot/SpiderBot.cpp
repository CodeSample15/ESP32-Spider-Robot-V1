#include "SpiderBot.h"

SpiderBot::SpiderBot(Adafruit_PWMServoDriver* driver) {
  backRight = Leg(driver, 0, 1, 2,
          {212, 420},
          {210, 580},
          {120, 503}); //was 100

  backLeft = Leg(driver, 3, 4, 5,
          {200, 420},
          {180, 580},
          {120, 510});

  frontLeft = Leg(driver, 6, 7, 8,
          {180, 390},
          {190, 580},
          {150, 530}); //was 130

  frontRight = Leg(driver, 9, 10, 11,
          {200, 405},
          {95, 500},
          {120, 510});
}

//move all legs to the same position
void SpiderBot::allLegs(float root, float arm, float wrist) {
  backRight.setPositions(root, arm, wrist);
  backLeft.setPositions(root, arm, wrist);
  frontLeft.setPositions(root, arm, wrist);
  frontRight.setPositions(root, arm, wrist);
}

//simple configurations
void SpiderBot::conf_stand() {
  allLegs(0, -0.2, 0.3);
}

void SpiderBot::conf_crouch() {
  allLegs(0, 1, -1);
}

void SpiderBot::tick() {
  backRight.tick();
  backLeft.tick();
  frontLeft.tick();
  frontRight.tick();
}

Leg* SpiderBot::getBackRight() {
  return &backRight;
}

Leg* SpiderBot::getBackLeft() {
  return &backLeft;
}

Leg* SpiderBot::getFrontLeft() {
  return &frontLeft;
}

Leg* SpiderBot::getFrontRight() {
  return &frontRight;
}