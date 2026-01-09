#include "Motor.h"

Motor::Motor() {
  id = -1;
  driver = NULL;
  limit = {DEFAULT_MOTOR_MIN, DEFAULT_MOTOR_MAX};
  usePI = false;
  speed = 1;
}

Motor::Motor(uint8_t id, Adafruit_PWMServoDriver* driver, limit_s limit) {
  this->id = id;
  this->driver = driver;
  this->limit = limit;

  usePI = false;
  speed = 1;
  
  lmidpoint = (limit.upper + limit.lower) / 2;
  target = lmidpoint; //initialize target to midpoint to avoid breaking stuff
}

void Motor::setTarget(float pos) {
  pos = constrain(pos, -1.0, 1.0);

  target = (pos * (lmidpoint - limit.lower)) + lmidpoint;
}

void Motor::setUsePI(bool usePI) {
  this->usePI = usePI;
}

void Motor::setSpeed(float speed) {
  speed = constrain(speed, 0.0, 1.0);

  this->speed = speed;
}

void Motor::tick() {
  if(speed==1)
    position = target; //use max speed if speed is 1
  else {
    if(usePI) 
    {
      
    } 
    else 
    {
      float change = MOTOR_MAX_SPEED * speed * (target-position>0 ? 1 : -1);

      if(abs(position-target) < change)
        position = target;
      else
        position += MOTOR_MAX_SPEED * speed * (target-position>0 ? 1 : -1);
    }
  }



  this->driver->setPWM(id, 0, (uint16_t)position);
}

bool Motor::targetReached() {
  return target == position;
}

uint16_t Motor::getPosition() {
  return position;
}
