// This program shakes a servo back and forth

#include <VarSpeedServo.h>

VarSpeedServo servo; // instantiate servo

int pos = 60;   // initial position
int pin = 10;   // analog pin servo is attached to
int shake = 10; // amount to shake servo
int speed = 10; // speed servo will move at

void setup() {
  servo.attach(pin); // declare analog pin servo is attached to
  servo.write(pos, speed, true); // write the initial position
}

void loop() {
  servo.write(pos - shake, speed, true); // move in the negative direction
  servo.write(pos + shake, speed, true); // move in the positive direction
}
