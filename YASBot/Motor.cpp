#include "motor.h"

Motor::Motor() {
  //bunch-o-defaults
  id = -1;
  driver = NULL;
  limit = {DEFAULT_MOTOR_MIN, DEFAULT_MOTOR_MAX};
  usePI = false;
  useSlew = false;
  speed = 1;
  integral = 0;
  slew = 0;
}

Motor::Motor(uint8_t id, Adafruit_PWMServoDriver* driver, bool reversed, limit_s limit) {
  this->id = id;
  this->driver = driver;
  this->limit = limit;

  this->reversed = reversed;

  usePI = false;
  useSlew = false;
  speed = 1;
  
  lmidpoint = (limit.upper + limit.lower) / 2;
  target = lmidpoint; //initialize target to midpoint to avoid breaking stuff

  integral = 0;
  slew = 0;
}

void Motor::setTarget(float pos) {
  pos = constrain(pos, -1.0, 1.0);

  if(reversed)
    pos*=-1;

  integral = 0;
  slew = 0;
  target = (pos * (lmidpoint - limit.lower)) + lmidpoint;
}

void Motor::setUsePI(bool usePI) {
  this->usePI = usePI;
}

void Motor::setUseSlew(bool useSlew) {
  this->useSlew = useSlew;
}

void Motor::setSpeed(float speed) {
  speed = constrain(speed, 0.0, 1.0);

  this->speed = speed;
}

void Motor::tick() {
  if(target == position)
    return;

  if(speed==1)
    position = target; //use max servo speed if speed is 1
  else {
    float change;

    if(usePI) 
    {
      float err = (float)target - position;

      integral = abs(err) > INTEGRAL_RANGE ? 
              0 : constrain(integral + err, -MAX_INTEGRAL, MAX_INTEGRAL);

      change = err * kP + (integral * kI);
    }
    else {
      change = MOTOR_MAX_SPEED * speed * (target-position>0 ? 1 : -1);
    }

    if(useSlew) {
      change = abs(slew) < abs(change) ? slew : change;
      slew += SLEW_RATE * (target-position>0 ? 1 : -1);
    }

    if(abs(position-target) < change) //if the change will cause the position to overshoot, just set the position to the target
      position = target;
    else
      position += change;
  }

  //send calculated position to PWM driver via I2C
  this->driver->setPWM(id, 0, (uint16_t)position);
}

void Motor::finishMoving() {
  while(!targetReached())
    tick();
}

bool Motor::targetReached() {
  return target == position;
}

uint16_t Motor::getPosition() {
  return position;
}
