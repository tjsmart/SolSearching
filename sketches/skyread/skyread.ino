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
    Serial.println("Begin skyread");
    for (int y = 0; y < 90; y++)
    {
        motorPos[0] = y;
        for (int x = 0; x < 180; x++)
        {
            motorPos[1] = x;
            tracker.setMotorPos(motorPos);
            tracker.readResistorDiff();
            tracker.printAll();
        }
    }
    Serial.println("End skyread");
    delay(forever);
}
