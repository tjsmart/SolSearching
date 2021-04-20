#pragma once

// index 0 and 2 of resistors will move motor 0
// index 1 and 3 of resistors will move motor 1
int resistors[] = {0, 1, 2, 3}; // resistor pins
int motors[] = {1, 2};          // motor pins

int moveDelay = 1000;           // delay between movements

int stepsPerRev = 200;          // our stepper is 200 steps per revolution (1.8 degree per step)
int revSpeed[2] = {10, 1};     // speed of each stepper in revolutions per minute (rpm)
int stepStyle[2] = {4, 4};      // style of stepping can be SINGLE (1), DOUBLE (2), INTERLEAVE (3), or MICROSTEP (4)

int stepSize[2] = {50, 10};     // step size to move the steppers before checking photoresistors again
