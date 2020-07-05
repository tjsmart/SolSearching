#include <solarTracker.hpp>
#include "setup.hpp"

solarTracker tracker(resistors, motors, pos);
int motorPos[2];

void setup()
{
    Serial.begin(9600);
    tracker.setup();
}

void loop()
{
    for (int x = 0; x < 180; x++)
    {
        motorPos[0] = x;
        for (int y = 0; y < 180; y++)
        {
            motorPos[1] = y;
            tracker.setMotorPos(motorPos);
            tracker.readResistorDiff();
            tracker.printAll();
        }
    }
}
