#include "Motor.h"

Motor::Motor(uint8_t id, Adafruit_PWMServoDriver* driver, limit_s limit) {
  this->id = id;
  this->driver = driver;
  this->limit = limit;
}

