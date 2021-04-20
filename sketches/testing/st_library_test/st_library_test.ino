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

//    for (int axis=0; axis < 2; axis++)
//    {
//        for (int dir=1; dir < 3; dir++)
//        {
//            tracker.moveMotor(axis, stepSize[axis], dir, stepStyle[axis]);
//            delay(moveDelay);
//        }
//    }

    delay(moveDelay);

}
