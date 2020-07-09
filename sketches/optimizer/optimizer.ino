#include <SolarTracker.hpp>
#include "setup.hpp"

SolarTracker tracker(resistors, motors, pos);

void setup()
{
    Serial.begin(9600);
    tracker.setup();
}

void loop()
{
    tracker.readResistorDiff();
    tracker.printAll();

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
