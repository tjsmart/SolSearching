/* 
    This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
    It won't work with v1.x motor shields! Only for the v2's with built in PWM
    control

    For use with the Adafruit Motor Shield v2 
    ---->  http://www.adafruit.com/products/1438

    This sketch is modified from:
    https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library/blob/master/examples/StepperTest/StepperTest.ino
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>


/*
    change these values as desired
*/

// our stepper is 200 steps per revolution (1.8 degree per step)
int steps_per_rev = 200;
// number of revolutions to turn stepper
int step_size = 1 * steps_per_rev;
// speed of stepper in revolutions per minute (rpm)
int rev_speed = 10;
// style of stepping can be SINGLE (1), DOUBLE (2), INTERLEAVE (3), or MICROSTEP (4)
int step_style = SINGLE;


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect two stepper motors to motor port #1 (M1 and M2) or #2 (M3 and M4)
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(steps_per_rev, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(steps_per_rev, 2);


void setup() {
    // Connect to serial monitor
    Serial.begin(9600);
    Serial.println("Stepper test!");

    // create with the default frequency 1.6KHz 
    AFMS.begin(); 

    // set the motor speeds
    myMotor1->setSpeed(rev_speed);
    myMotor2->setSpeed(rev_speed);
}

void loop() {
    /*
        This program will step motor1 forward by step_size (defined above),
        then step motor2 forward, then step motor1 backwards, then step motor2
        backwards, looping this process indefinitely.
    */

    Serial.println("Stepping motor1 FORWARD");
    myMotor1->step(step_size, FORWARD, step_style); 
    Serial.println("Stepping motor2 FORWARD");
    myMotor2->step(step_size, FORWARD, step_style); 
    Serial.println("Stepping motor1 BACKWARD");
    myMotor1->step(step_size, BACKWARD, step_style);
    Serial.println("Stepping motor2 BACKWARD");
    myMotor2->step(step_size, BACKWARD, step_style);
}
