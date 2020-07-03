#pragma once

class solarTracker
{
protected:
    static const int numResistors = 4;
    static const int numMotors = 2;
    int resistorPins[numResistors];
    int motorPins[numMotors];

public:
    solarTracker(int* resistorPins, int* motorPins);
    ~solarTracker();

    int* getResistorPins();
    int* getMotorPins();
    void printResistorPins() const;
    void printMotorPins() const;
};

