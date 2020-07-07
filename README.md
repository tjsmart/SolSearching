SolSearching Repository
===

Getting started (using solarTracker library)
---
From cloned repository:

1. Download or clone this repository onto your computer
2. Copy or symlink the solarTracker folder (not the entire repo) to the location of your arduino libraries.
    - On Mac: `cp -r solarTracker ~/Documents/Arduino/Library` or `ln -fs $PWD/solarTracker ~/Documents/Arduino/Library`

From release:

1. Download from the latest release `solarTracker.zip`.
2. In the arduino IDE, navigate to Sketch->Include Library->Add .ZIP Library...
3. Select the `solarTracker.zip` file you just downloaded.

Getting started (using example sketches)
---

The optimizer sketch, configures the solarTracker to search for the brightest light source and track it over time.
To upload the solar tracker optimizer sketch to your arduino open `sketches/optimizer/optimizer.ino` in the arduino IDE and upload it to your arduino.

The skyread sketch, configures the solarTracker to take a survey of the entire sky and print the values of the photoresistors to the serial monitor.
To upload the skyread sketch open `sketches/skyread/skyread.ino` with the arduino IDE.
Also, try the live python plotting and recording under `sketches/skyread/python/skyread.py`.


Debugging
---
There are several tests present under the folder `tests` to confirm that your arduino and its components are working properly.

Contents of this repository
---
- [doc](doc/) -> documentation including a todo list and some resources
- [sketches](sketches/) -> arduino sketches
- [solarTracker](solarTracker/) -> solarTracker library


Expected pin ordering in current version (**unconfirmed**)
---

For the photoresistors, looking down the shaft of the cross:

```
       top(2)  
       \    /  
        \  /  
 left(3) \/ right(5)  
         /\  
        /  \  
       /    \  
       bottom(4)  
```

For the servos, the vertical (horizontal) servo should be attached to pin 9, 10.

Worst case scenario, just troubleshoot it with a test light source and reset which pins in the `sketches/optimizer/setup.hpp`

