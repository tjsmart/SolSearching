#include "solarTracker.hpp"
#include "setup.hpp"

solarTracker tracker(resistors, motors, pos);

void setup()
{
    // Include for debugging information
    Serial.begin(9600);
    // Run the trackers setup routine
    tracker.setup();
}

void loop()
{
    tracker.readResistorDiff();
    tracker.printResistorDiff();

    if (tracker.isThereLight())
    {
        //if light source is unoptimized
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
