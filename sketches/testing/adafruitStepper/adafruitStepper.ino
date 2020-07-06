#include <AFMotor.h>

// Connect a stepper motor with 200 steps per revolution (1.8 degree per step)
// to motor port #1 (M1 and M2) or #2 (M3 and M4)
AF_Stepper motor(200, 2);

void setup()
{
    // Establish serial connection
    Serial.begin(9600);
    Serial.println("Stepper test!");
    // Set motor speed in rpm
    motor.setSpeed(10);
}

void loop()
{
    // motor.step(number of steps, direction, style)

    Serial.println("Single coil steps");
    motor.step(100, FORWARD, SINGLE); 
    motor.step(100, BACKWARD, SINGLE); 

    Serial.println("Double coil steps");
    motor.step(100, FORWARD, DOUBLE); 
    motor.step(100, BACKWARD, DOUBLE);

    Serial.println("Interleave coil steps");
    motor.step(100, FORWARD, INTERLEAVE); 
    motor.step(100, BACKWARD, INTERLEAVE); 

    Serial.println("Micrsostep steps");
    motor.step(100, FORWARD, MICROSTEP); 
    motor.step(100, BACKWARD, MICROSTEP); 
}
