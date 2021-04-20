#include <SolarTracker.hpp>
#include "setup.hpp"

SolarTracker tracker(resistors, motors);

void setup()
{
    Serial.begin(9600);
    tracker.setup(revSpeed, stepStyle);
}

void loop()
{
    tracker.readResistorDiff();
    tracker.printAll();

    if (tracker.isThereLight())
    {
        if (tracker.isUnoptimized())
        {
            // // this optimize is likely unideal for these steppers
            // tracker.optimize();
            // tracker.printMotorDir();

            // individually optimize both axis
            for (int axis=0; axis < 2; axis++)
                tracker.fullAxisOptimize(axis, stepSize[axis]);
        }
        else
        {
            Serial.println("Optimized! :)");
            delay(restTime);
        }
    }
    else
    {
        Serial.println("There is no light");
        delay(sleepTime);
    }
}
