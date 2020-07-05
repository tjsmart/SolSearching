#include "solarTracker.hpp"
#include <Arduino.h>
#include <VarSpeedServo.h>

// [√] photoresistor pins as int array
// [√] servo pins as int array
// [√] add motors as an attribute
// [√] constructor should pass prPins, srvPins, startingPos
// [√] setup method
// [√] read method
// [√] optimize method
// [X] how to handle bother servos and steppers (perhaps type of motors should be specified at compile time? (with ifdef))
// [X] reorganize this file to make the order match hpp

// constants
const int solarTracker::numResistors;
const int solarTracker::numMotors;

// constructor
solarTracker::solarTracker(int resistorPins[4], int motorPins[2], int motorPos[2])
{
    for (int i = 0; i < this->numResistors; i++)
        this->resistorPins[i] = resistorPins[i];
    for (int i = 0; i < this->numMotors; i++)
    {
        this->motorPins[i] = motorPins[i];
        this->motorPos[i] = motorPos[i];
    }
}

// deconstructor
solarTracker::~solarTracker()
{
}

// attach pins and write initial positions
void solarTracker::setup() const
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
        motor[i].attach(motorPins[i]);
        motor[i].write(motorPos[i], 10, true);
    }
}

// return the value of resistorPins
int *solarTracker::getResistorPins()
{
    return resistorPins;
}

// return the value of motorPins
int *solarTracker::getMotorPins()
{
    return motorPins;
}

// return the of motorPos
int *solarTracker::getMotorPos()
{
    return motorPos;
}

// analog read the resistorPins and store to resistorValues
int *solarTracker::readResistorValues()
{
    for (int i = 0; i < numResistors; i++)
        resistorValues[i] = analogRead(resistorPins[i]);
    return resistorValues;
}

// calls readResistorValues and then computes difference between top/bottom, left/right
int *solarTracker::readResistorDiff()
{
    readResistorValues();
    for (int i = 0; i < numMotors; i++)
    {
        resistorDiff[i] = resistorValues[i + 2] - resistorValues[i];
    }
    return resistorDiff;
}


// print values of the motorpos, resistors and their difference
void solarTracker::printAll() const
{
    for (int i = 0; i < numMotors; i++)
    {
        Serial.print(motorPos[i]);
        Serial.print("\t");
    }
    for (int i = 0; i < numResistors; i++)
    {
        Serial.print(resistorValues[i]);
        Serial.print("\t");
    }
    for (int i = 0; i < numMotors; i++)
    {
        Serial.print(resistorDiff[i]);
        if (i != (numMotors - 1))
            Serial.print("\t");
    }
    Serial.println();
}

// print the values of the calculated motor delta (how much they were moved in the last step)
void solarTracker::printMotorDelta() const
{
    for (int i = 0; i < numMotors; i++)
    {
        Serial.print(motorDelta[i]);
        if (i != (numMotors - 1))
            Serial.print("\t");
    }
    Serial.println();
}

// returns true if any resistors are below the darkThresh
bool solarTracker::isThereLight()
{
    for (int i = 0; i < numResistors; i++)
        if (resistorValues[i] < darkThresh)
            return true;
    return false;
}

// returns true if any resistorDiff is above optThresh
bool solarTracker::isUnoptimized()
{
    for (int i = 0; i < numMotors; i++)
        if (abs(resistorDiff[i]) > optThresh)
            return true;
    return false;
}

// computes motorDelta, and updates motorPos to optimize the positions
void solarTracker::optimize()
{
    for (int i = 0; i < numMotors; i++)
    {
        motorDelta[i] = resistorDiff[i] / alpha;
        motorPos[i] = motorPos[i] + motorDelta[i];
        motor[i].write(motorPos[i], 10, true);
    }
}


void solarTracker::setMotorPos(int *motorPos) 
{
    for (int i = 0; i < numMotors; i++)
    {
        this->motorPos[i] = motorPos[i];
        motor[i].write(this->motorPos[i], 10, true);
    }
}
