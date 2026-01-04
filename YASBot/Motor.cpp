#include "Motor.h"

Motor::Motor(uint8_t id, Adafruit_PWMServoDriver* driver, limit_s limit) {
  this->id = id;
  this->driver = driver;
  this->limit = limit;
}

void Motor::setTarget(int8_t pos) {

}

void Motor::setUsePD(bool usePD) {

}

void Motor::setSpeed(float speed) {

}

void Motor::tick() {
  

  this->driver->setPWM(this->id, 0, this->position);
}

bool Motor::targetReached() {

}
