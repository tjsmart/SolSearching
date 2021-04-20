#pragma once

#include <Wire.h>
#include <Adafruit_MotorShield.h>

class SolarTracker
{
protected:
    static const int numResistors = 4;      // number of (photo)resistors
    static const int numMotors = 2;         // number of motors
    static const int stepsPerRev = 200;     // steps per revolution

    int resistorPins[numResistors];         // pins the resistors are attached to
    int motorPorts[numMotors];              // pins the motors are attached to

    int resistorValues[numResistors];       // current values of the resistors
    int resistorDiff[numMotors];            // current difference between top/bottom, left/right



    Adafruit_MotorShield AFMS = Adafruit_MotorShield();     // Motor shield object with the default I2C address
    // Adafruit_StepperMotor *motor[numMotors];                // Stepper motors
    Adafruit_StepperMotor *motor[numMotors] = {AFMS.getStepper(stepsPerRev, 1), AFMS.getStepper(stepsPerRev, 2)};

    int motorDir[numMotors];                                // Movement of motors can be 0 (NONE), 1 (FORWARD), 2 (BACKWARD)
    int stepStyle[numMotors];                                          // Can be 1 (SINGLE), 2 (DOUBLE), 3 (INTERLEAVE), or 4 (MICROSTEP)

    int darkThresh = 1000;                  // threshold to consider when there is no light
    int optThresh = 50;                     // threshold to consider when the SolarTracker is optimized

    // these could be moved to public but would required sophisticated usage, keeping them private for now for safety
    void setup();
    void setup(int *revSpeed);


public:
    // SolarTracker(int *resistorPins, int *motorPins, int *motorPos);
    SolarTracker(int *resistorPins, int *motorPorts);
    ~SolarTracker();

    int *getResistorPins();
    int *getMotorPorts();
    // int *getMotorPos();

    int *readResistorValues();
    int *readResistorDiff();

    // void setMotorPos(int *motorPos);
    void moveMotor(int axis, int stepSize, int stepDir, int stepStyle);

    void printAll() const;
    void printMotorDir() const;

    void setup(int *revSpeed, int *stepStyle);

    bool isThereLight();
    bool isUnoptimized();
    void optimize();

    void fullAxisOptimize(int axis, int stepSize);
    void fullAxisOptimize(int axis);
};
