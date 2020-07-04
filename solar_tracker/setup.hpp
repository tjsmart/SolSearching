#pragma once

// digital pins
int sensorTwo = 5;
int sensorThree = 3;
int sensorFour = 2;
int sensorFive = 4;

// analog input pins
int inputTwo = 5;
int inputThree = 3;
int inputFour = 2;
int inputFive = 4;

// servo pins
int vservoPin = 9;
int hservoPin = 10;

// starting position of the servo
int hpos = 85;
int vpos = 62;

// various parameters for the operation of the tracker
int darkthres = 1000;   // defines how dark is dark
int thresh = 50;        // threshold to define when to move
int alpha = 100;        // move = diff / alpha
int rest_time = 1e4;    // time to wait when the light source is optimized
int sleep_time = 6e4;   // time to wait when no light is present
