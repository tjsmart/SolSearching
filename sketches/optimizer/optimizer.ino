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
    tracker.readResistorDiff();
    tracker.printResistorDiff();

    if (tracker.isThereLight())
    {
        if (tracker.isUnoptimized())
        {
            tracker.optimize();
            tracker.printMotorDelta();
        }
        else
        {
            Serial.println("Optimized! :)");
            delay(rest_time);
        }
    }
    else
    {
        Serial.println("There is no light");
        delay(sleep_time);
    }
}
