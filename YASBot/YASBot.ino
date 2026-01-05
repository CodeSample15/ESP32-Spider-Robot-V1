#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Robot.h"

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot spider = Robot(&pwm);

void setup() {
  Serial.begin(9600);

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10); //idk if this is necessary but it's in the example code and won't cause much disruption soooooo we're keeping it (if it aint broke)
}

void loop() {
  spider.conf_crouch();
  spider.tick();
  sleep(2);
  spider.conf_stand();
  spider.tick();
  sleep(2);
}
