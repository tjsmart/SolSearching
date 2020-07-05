#include <solarTracker.hpp>
#include "setup.hpp"

solarTracker tracker(resistors, motors, pos);

void setup()
{
    Serial.begin(9600);
    tracker.setup();
}

void loop()
{
    for (int x = 0, x < 180, x++)
    {
        for (int y = 0, y < 180, y++)
        {
            tracker.moveMotors(x, y);
            tracker.readResistorDiff();
            tracker.printResistorDiff();
        }
    }
}
