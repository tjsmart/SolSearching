#include "SolarTracker.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>


// constants
const int SolarTracker::numResistors;
const int SolarTracker::numMotors;

SolarTracker::SolarTracker(int resistorPins[4], int motorPorts[2])
{
    // this->constructor(resistorPins, motorPorts, stepsPerRev);
    for (int i = 0; i < this->numResistors; i++)
    {
        this->resistorPins[i] = resistorPins[i];
    }
    for (int i = 0; i < this->numMotors; i++)
    {
        // if ((motorPorts[i] != 1) and (motorPorts[i] != 2)) this->die();
        this->motorPorts[i] = motorPorts[i];
    }
}

// destructor
SolarTracker::~SolarTracker()
{
}

// return the value of resistorPins
int *SolarTracker::getResistorPins()
{
    return resistorPins;
}

// return the value of motorPorts
int *SolarTracker::getMotorPorts()
{
    return motorPorts;
}

// analog read the resistorPins and store to resistorValues
int *SolarTracker::readResistorValues()
{
    for (int i = 0; i < numResistors; i++)
    {
        resistorValues[i] = analogRead(resistorPins[i]);
    }
    return resistorValues;
}

// calls readResistorValues and then computes difference between top/bottom, left/right
int *SolarTracker::readResistorDiff()
{
    readResistorValues();
    for (int i = 0; i < numMotors; i++)
    {
        resistorDiff[i] = resistorValues[i + 2] - resistorValues[i];
    }
    return resistorDiff;
}

// print values of the resistors and their difference
void SolarTracker::printAll() const
{
    for (int i = 0; i < numResistors; i++)
    {
        Serial.print(resistorValues[i]);
        Serial.print("\t");
    }
    for (int i = 0; i < numMotors; i++)
    {
        Serial.print(resistorDiff[i]);
        if (i != (numMotors - 1))
        {
            Serial.print("\t");
        }
    }
    Serial.println();
}

// print the values of the calculated motor delta (how much they were moved in the last step)
void SolarTracker::printMotorDir() const
{
    for (int i = 0; i < numMotors; i++)
    {
        Serial.print(motorDir[i]);
        if (i != (numMotors - 1))
        {
            Serial.print("\t");
        }
    }
    Serial.println();
}

// attach pins for photoresistor and instatiate motors
void SolarTracker::setup(int stepsPerRev)
{
    // establish resistor pins as output and write them as HIGH
    for (int i = 0; i < this->numResistors; i++)
    {
        pinMode(resistorPins[i], OUTPUT);
        digitalWrite(resistorPins[i], HIGH);
    }

    // attach servos and write their inital positions
    for (int i = 0; i < this->numMotors; i++)
    {
        // Connect two stepper motors to the motor ports
        this->motor[i] = this->AFMS.getStepper(stepsPerRev, motorPorts[i]);
    }
}

void SolarTracker::setup(int stepsPerRev, int revSpeed[2])
{
    // this->setup(stepsPerRev);
    setup(stepsPerRev);
    // set speed of each stepper
    for (int i = 0; i < this->numMotors; i++)
    {
        this->motor[i]->setSpeed(revSpeed[i]);
    }
}

void SolarTracker::setup(int stepsPerRev, int revSpeed[2], int stepStyle)
{
    // bool stepStyleIsValid = false;
    // for (int i = 1; i <= 4; i++)
    // {
    //     if (stepStyle == i) stepStyleIsValid = true;
    // }
    // if (!stepStyleIsValid) this->die();

    setup(stepsPerRev, revSpeed);
    // set a default step style -- otherwise user must specify
    this->stepStyle = stepStyle;
}


// returns true if any resistors are below the darkThresh
bool SolarTracker::isThereLight()
{
    for (int i = 0; i < numResistors; i++)
    {
        if (resistorValues[i] < darkThresh)
        {
            return true;
        }
    }
    return false;
}

// returns true if any resistorDiff is above optThresh
bool SolarTracker::isUnoptimized()
{
    for (int i = 0; i < numMotors; i++)
    {
        if (abs(resistorDiff[i]) > optThresh)
        {
            return true;
        }
    }
    return false;
}

// computes motorDir, and updates motorPos to optimize the positions
void SolarTracker::optimize()
{
    int stepSize = 1;
    for (int i = 0; i < numMotors; i++)
    {
        if (resistorDiff[i] > optThresh)
        {
            motorDir[i] = BACKWARD;
        } else if (resistorDiff[i] < -optThresh) {
            motorDir[i] = FORWARD;
        } else {
            motorDir[i] = 0;
            continue;
        }

        motor[i]->step(stepSize, motorDir[i], stepStyle);
    }
}

// same as above but fully optimizes along a single axis (dir should be 0 or 1)
void SolarTracker::fullAxisOptimize(int axis, int stepSize)
{
    // read resistors and print their values
    readResistorDiff();
    printAll();

    // determine movement direction
    if (resistorDiff[axis] > optThresh)
    {
        motorDir[axis] = BACKWARD;
    } else if (resistorDiff[axis] < -optThresh) {
        motorDir[axis] = FORWARD;
    } else {
        motorDir[axis] = 0;
    }

    // print movement
    Serial.print("Moving motor:\t");
    Serial.print(axis);
    Serial.print("\t");
    Serial.print(motorDir[axis]);
    Serial.println();

    if (motorDir[axis] == 0)
    {
        Serial.println("Axis Optimized! :)");
        return;
    } else {
        motor[axis]->step(stepSize, motorDir[axis], stepStyle);
        // recurse
        fullAxisOptimize(axis, stepSize);
    }
}

void SolarTracker::fullAxisOptimize(int axis)
{
    // defaults stepSize to 1
    fullAxisOptimize(axis, 1);
}
