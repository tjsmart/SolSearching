#include "solarTracker.hpp"
#include <iostream>

// [√] photoresistor pins as int array
// [√] servo pins as int array
// [X] dictionary instead of array? so labeling is clearer perhaps. I think I like this better
// [X] constructor should pass prPins, srvPins, startingPos
// [X] setup method
// [X] read method
// [X] optimize method

// construct solarTracker
const int solarTracker::numResistors;
const int solarTracker::numMotors;
solarTracker::solarTracker(int resistorPins[4], int motorPins[2])
{
    for (int i=0; i < this->numResistors; i++){this->resistorPins[i] = resistorPins[i];}
    for (int i=0; i < this->numMotors; i++){this->motorPins[i] = motorPins[i];}
}

solarTracker::~solarTracker()
{
}

int* solarTracker::getResistorPins()
{
    return resistorPins;
}

int* solarTracker::getMotorPins()
{
    return motorPins;
}

void solarTracker::printResistorPins() const
{
    for (int i=0; i < this->numResistors; i++)
    {
        std::cout << resistorPins[i] << std::endl;
    }
}

void solarTracker::printMotorPins() const
{
    for (int i=0; i < this->numMotors; i++)
    {
        std::cout << motorPins[i] << std::endl;
    }
}

