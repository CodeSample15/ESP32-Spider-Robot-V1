#include "Robot.h"

Robot::Robot(Adafruit_PWMServoDriver* driver) {
  backRight = Leg(driver, 0, 1, 2,
          {212, 420},
          {210, 580},
          {100, 503});

  backLeft = Leg(driver, 3, 4, 5,
          {200, 420},
          {180, 580},
          {120, 510});

  frontLeft = Leg(driver, 6, 7, 8,
          {180, 390},
          {190, 580},
          {130, 530});

  frontRight = Leg(driver, 9, 10, 11,
          {200, 405},
          {95, 500},
          {120, 510});
}

//move all legs to the same position
void Robot::allLegs(float root, float arm, float wrist) {
  backRight.setPositions(root, arm, wrist);
  backLeft.setPositions(root, arm, wrist);
  frontLeft.setPositions(root, arm, wrist);
  frontRight.setPositions(root, arm, wrist);
}

//simple configurations
void Robot::conf_stand() {
  allLegs(0, -0.2, 0.3);
}

void Robot::conf_crouch() {
  allLegs(0, 1, -1);
}

void Robot::tick() {
  backRight.tick();
  backLeft.tick();
  frontLeft.tick();
  frontRight.tick();
}

Leg* Robot::getBackRight() {
  return &backRight;
}

Leg* Robot::getBackLeft() {
  return &backLeft;
}

Leg* Robot::getFrontLeft() {
  return &frontLeft;
}

Leg* Robot::getFrontRight() {
  return &frontRight;
}