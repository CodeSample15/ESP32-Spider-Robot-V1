#include <Adafruit_PWMServoDriver.h>
#include "motor.h"

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {
  // put your main code here, to run repeatedly:

}
