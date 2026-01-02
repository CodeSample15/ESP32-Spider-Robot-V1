#pragma once

#include <Adafruit_PWMServoDriver.h>

//default pulse lengths for full range of motion of the servos (out of 4096)
//calculated by pulse length (μsec) / 4. Pulse length from amazon page: https://www.amazon.com/dp/B0BKPL2Y21?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1
#define DEFAULT_MOTOR_MAX 625
#define DEFAULT_MOTOR_MIN 125

//tuning values for PD loop
#define kP 1
#define kD 0

// struct to define the upper and lower limit of a servo motor for consistent range of motion between limbs of the robot
typedef struct {
  uint16_t lower;
  uint16_t upper;
} limit_s;

class motor {
  public:
    motor(uint8_t id, Adafruit_PWMServoDriver* driver, limit_s limit={DEFAULT_MOTOR_MIN, DEFAULT_MOTOR_MAX});
    
    void setTarget(int8_t pos);
    void setUsePD(bool usePD); //PD control loop
    void setSpeed(float speed);

    void tick();

  private:
    limit_s limit;

    uint16_t target;
    uint16_t position; //position moves towards target at a specific speed each "tick()"

    float speed;

    bool usePD;
}