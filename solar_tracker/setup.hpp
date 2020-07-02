#pragma once

// digital pins
const int sensorTwo = 5;
const int sensorThree = 3;
const int sensorFour = 2;
const int sensorFive = 4;

// analog input pins
const int inputTwo = 5;
const int inputThree = 3;
const int inputFour = 2;
const int inputFive = 4;

// starting position of the servo
int hpos = 85;
int vpos = 62;

// various parameters for the operation of the tracker
int darkthres = 1000;   // defines how dark is dark
int hthres = 60;        // threshold to define when to move horizontally
int vthres = 60;        // threshold to define when to move vertically
int hmove = 5;          // amount to move horizontal position
int vmove = 5;          // amount to move vertical position
int rest_time = 10;     // time to wait when the light source is optimized
int sleep_time = 10;    // time to wait when no light is present
int alpha = 1;          // moveh = diffh * alpha (unused)
int beta = 1;           // movev = diffv * beta (unused)
