#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Robot.h"

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Motor test = Motor(2, &pwm, {120, 503});

void setup() {
  Serial.begin(9600);

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  test.setUsePI(false);
  test.setSpeed(0.5);
}

void loop() {
  test.setTarget(0.5);

  while(!test.targetReached()) {
    test.tick();
  }

  test.setTarget(-0.5);

  while(!test.targetReached()) {
    test.tick();
  }
}
