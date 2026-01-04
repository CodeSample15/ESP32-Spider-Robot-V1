#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int position = 375;
String fromComputer;

void setup() {
  Serial.begin(9600);
  Serial.println("Testing servo");

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10); //idk if this is necessary but it's in the example code and won't cause much disruption soooooo we're keeping it (if it aint broke)
}

void loop() {
  fromComputer = Serial.readString();

  // #define DEFAULT_MOTOR_MAX 625
  // #define DEFAULT_MOTOR_MIN 125
  if(fromComputer != "") {
    if(fromComputer[0] == 'u')
      position++;
    else if(fromComputer[0] == 'd')
      position--;
    else
      position = fromComputer.toInt();

    Serial.println((String)position);
  }
  
  pwm.setPWM(11, 0, position);
}
