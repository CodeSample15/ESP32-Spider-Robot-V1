#include "Motor.h"

Motor::Motor() {
  id = -1;
  driver = NULL;
  limit = {DEFAULT_MOTOR_MIN, DEFAULT_MOTOR_MAX};
}

Motor::Motor(uint8_t id, Adafruit_PWMServoDriver* driver, limit_s limit) {
  this->id = id;
  this->driver = driver;
  this->limit = limit;
  
  lmidpoint = (limit.upper + limit.lower) / 2;
  target = lmidpoint; //initialize target to midpoint to avoid breaking stuff
}

void Motor::setTarget(float pos) {
  pos = constrain(pos, -1.0, 1.0);

  this->target = (pos * (lmidpoint - this->limit.lower)) + lmidpoint;
}

void Motor::setUsePD(bool usePD) {
  this->usePD = usePD;
}

void Motor::setSpeed(float speed) {
  speed = constrain(speed, 0.0, 1.0);

  this->speed = speed;
}

void Motor::tick() {
  position = target;

  this->driver->setPWM(id, 0, position);
}

bool Motor::targetReached() {
  return target == position;
}
