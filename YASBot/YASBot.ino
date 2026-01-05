#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Leg.h"

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Leg backRight = Leg(&pwm, 0, 1, 2,
          {212, 420},
          {210, 585},
          {100, 503});

Leg backLeft = Leg(&pwm, 3, 4, 5,
          {200, 420},
          {180, 580},
          {120, 510});

Leg frontLeft = Leg(&pwm, 6, 7, 8,
          {180, 390},
          {190, 585},
          {130, 530});

Leg frontRight = Leg(&pwm, 9, 10, 11,
          {200, 405},
          {95, 500},
          {120, 510});

void setup() {
  Serial.begin(9600);

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10); //idk if this is necessary but it's in the example code and won't cause much disruption soooooo we're keeping it (if it aint broke)
}

void loop() {
  backRight.setPositions(0, -0.2, 0.3);
  backLeft.setPositions(0, -0.2, 0.3);
  frontLeft.setPositions(0, -0.2, 0.3);
  frontRight.setPositions(0, -0.2, 0.3);

  backRight.tick();
  backLeft.tick();
  frontLeft.tick();
  frontRight.tick();
}
