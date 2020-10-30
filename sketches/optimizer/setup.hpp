#pragma once

int resistors[] = {2, 5, 4, 3}; // resistor pins
int motors[] = {1, 2};          // motor ports

int restTime = 10000;          // time to wait when the light source is optimized
int sleepTime = 60000;         // time to wait when no light is present

int stepsPerRev = 200;          // our stepper is 200 steps per revolution (1.8 degree per step)
int revSpeed[2] = {10, 10};     // speed of each stepper in revolutions per minute (rpm)
int stepStyle = 2;              // style of stepping can be SINGLE (1), DOUBLE (2), INTERLEAVE (3), or MICROSTEP (4)

int stepSize[2] = {1, 1};      // step size to move the steppers before checking photoresistors again
