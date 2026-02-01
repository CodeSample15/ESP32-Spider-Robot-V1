#include <Adafruit_PWMServoDriver.h>
#include "SpiderBot.h"

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define PI 3.14

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
SpiderBot robot = SpiderBot(&pwm);

float animation = 0;

void setup() {
  Serial.begin(9600);

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  robot.conf_crouch();
  robot.tick();

  delay(500);

  robot.setSpeeds(0.8, 0.8, 0.8);
}

void loop() {
  robot.getFrontRight()->simple_walk_cycle(animation);
  robot.getFrontLeft()->simple_walk_cycle(animation + PI);
  robot.getBackRight()->simple_walk_cycle(-animation - PI);
  robot.getBackLeft()->simple_walk_cycle(-animation);

  robot.finishMoving();

  animation += 0.05;
}
