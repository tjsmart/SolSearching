#include <Wire.h>
#include <Adafruit_MotorShield.h>


/*-------------------------------------------------------
    MOTOR INITIALIZATION
-------------------------------------------------------*/

// our stepper is 200 steps per revolution (1.8 degree per step)
int steps_per_rev = 200;
// number of revolutions to turn stepper
int step_size[] = {10, 20};
// speed of stepper in revolutions per minute (rpm)
int rev_speed = 10;
// style of stepping can be SINGLE (1), DOUBLE (2), INTERLEAVE (3), or MICROSTEP (4)
int step_style = MICROSTEP;


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect two stepper motors to motor port #1 (M1 and M2) or #2 (M3 and M4)
// Adafruit_StepperMotor *motor1 = AFMS.getStepper(steps_per_rev, 1);
// Adafruit_StepperMotor *motor2 = AFMS.getStepper(steps_per_rev, 2);
Adafruit_StepperMotor *motor[] = {AFMS.getStepper(steps_per_rev, 1), AFMS.getStepper(steps_per_rev, 2)};


/*-------------------------------------------------------
    PHOTORESISTOR INITIALIZATION
-------------------------------------------------------*/

int pin[] = {0, 1, 2, 3};
int prValue[4];        // where the photoresistor value will be stored


/*-------------------------------------------------------
    SETUP
-------------------------------------------------------*/

void setup() {
    // Connect to serial monitor
    Serial.begin(9600);

    /*-------------------------------------------------------
        MOTOR SETUP
    -------------------------------------------------------*/
    Serial.println("Motor Setup");
    // create with the default frequency 1.6KHz
    AFMS.begin();
    // set the motor speed
    // motor1->setSpeed(rev_speed);
    for (int i = 0; i < 2; i++)
        motor[i]->setSpeed(rev_speed);

    /*-------------------------------------------------------
        PHOTORESISTOR SETUP
    -------------------------------------------------------*/
    Serial.println("Photoresistor Setup");
    for (int i = 0; i < 4; i++)
    {
        if ( i != 1)
        {
            pinMode(pin[i], OUTPUT);     // set sensorPin to be output
            digitalWrite(pin[i], HIGH);  // set sensorPin to HIGH
        }
        else
        {
            pinMode(7, OUTPUT);     // set sensorPin to be output
            digitalWrite(7, HIGH);  // set sensorPin to HIGH
        }
    }

}


/*-------------------------------------------------------
    LOOP
-------------------------------------------------------*/

void loop() {

    /*-------------------------------------------------------
        MOTOR LOOP
    -------------------------------------------------------*/

    // Serial.println("Stepping motor1 FORWARD");
    // motor1->step(step_size[0], FORWARD, step_style);
    // delay(1000);
    // Serial.println("Stepping motor1 BACKWARD");
    // motor1->step(step_size[0], BACKWARD, step_style);
    // delay(1000);
    for (int i = 0; i < 2; i++)
    {
        Serial.print("Moving Motor ");
        Serial.print(i);
        Serial.print(" FORWARD");
        motor[i]->step(step_size[i], FORWARD, step_style);
        delay(1000);
        Serial.println(" BACKWARD");
        motor[i]->step(step_size[i], BACKWARD, step_style);
        delay(1000);
    }

    /*-------------------------------------------------------
        PHOTORESISTOR LOOP
    -------------------------------------------------------*/

    Serial.print("Reading .... ");
    for (int i = 0; i < 4; i++)
    {
        prValue[i] = analogRead(pin[i]); // Read value of the photoresistor
        Serial.print(pin[i]);
        Serial.print(" = ");
        Serial.print(prValue[i]);        // Write the value to the serial monitor
        if (i != 3) Serial.print(" , ");
    }
    Serial.println();
    delay(1000);
}
