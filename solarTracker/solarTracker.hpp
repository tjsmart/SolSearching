#pragma once
#include <VarSpeedServo.h>

class solarTracker
{
protected:
    static const int numResistors = 4;      // number of (photo)resistors
    static const int numMotors = 2;         // number of motors

    int resistorPins[numResistors];         // pins the resistors are attached to
    int motorPins[numMotors];               // pins the motors are attached to

    int resistorValues[numResistors];       // current values of the resistors
    int resistorDiff[numMotors];            // current difference between top/bottom, left/right

    VarSpeedServo motor[numMotors];         // the motors (see online doc for more info)
    int motorPos[numMotors];                // the position of the motors
    int motorDelta[numMotors];              // the change to the position made in last step

    int darkThresh = 1000;                  // threshold to consider when there is no light
    int optThresh = 50;                     // threshold to consider when the solarTracker is optimized
    int alpha = 100;                        // motorDelta = resistorDiff / alpha

public:
    solarTracker(int *resistorPins, int *motorPins, int *motorPos);
    ~solarTracker();

    int *getResistorPins();
    int *getMotorPins();
    int *getMotorPos();

    int *readResistorValues();
    int *readResistorDiff();

    void setMotorPos(int *motorPos); 

    void printAll() const;
    void printMotorDelta() const;

    void setup() const;

    bool isThereLight();
    bool isUnoptimized();
    void optimize();
};
