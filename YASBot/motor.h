#pragma once

#include <Adafruit_PWMServoDriver.h>

//default pulse lengths for full range of motion of the servos (out of 4096)
//calculated by pulse length (μsec) / 4. Pulse length from amazon page: https://www.amazon.com/dp/B0BKPL2Y21?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1
#define DEFAULT_MOTOR_MAX 625
#define DEFAULT_MOTOR_MIN 125

//this value was guessed and then slowly adjusted to represent roughly how fast an SG90 moves (in pulse length / clock cycle) ¯\_(ツ)_/¯
#define MOTOR_MAX_SPEED 0.6

//tuning values for PD loop
#define kP 0.005
#define kI 0.001

//min error size where integral kicks in
#define INTEGRAL_RANGE 50
#define MAX_INTEGRAL 10

//slew
#define SLEW_RATE 0.0004

// struct to define the upper and lower limit of a servo motor for consistent range of motion between limbs of the robot
typedef struct {
  uint16_t lower;
  uint16_t upper;
} limit_s;

class Motor {
  public:
    Motor();
    Motor(uint8_t id, Adafruit_PWMServoDriver* driver, bool reversed=false, limit_s limit={DEFAULT_MOTOR_MIN, DEFAULT_MOTOR_MAX});
    
    void setTarget(float pos); // [-1.0] - [1.0]
    void setUsePI(bool usePI); //PI control loop
    void setUseSlew(bool useSlew);
    void setSpeed(float speed);

    void tick();
    void finishMoving(); //one call to move until target reached

    bool targetReached(); //returns whether or not the motor has reached its desired target
    uint16_t getPosition();

  private:
    uint8_t id;
    Adafruit_PWMServoDriver* driver;

    bool reversed;

    limit_s limit;
    uint16_t lmidpoint;

    uint16_t target;
    float position; //position moves towards target at a specific speed each "tick()"

    float integral;
    float slew;

    float speed;
    bool usePI;
    bool useSlew;
};