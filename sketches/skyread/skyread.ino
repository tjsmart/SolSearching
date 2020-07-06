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
    for (int x = 40; x < 50; x++)
    {
        motorPos[0] = x;
        for (int y = 40; y < 50; y++)
        {
            motorPos[1] = y;
            tracker.setMotorPos(motorPos);
            tracker.readResistorDiff();
            tracker.printAll();
        }
    }
    Serial.println("End skyread");
    delay(forever);
}
