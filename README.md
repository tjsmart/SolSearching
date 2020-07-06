SolSearching Repository
===

Getting started
---
First you will need to install the solarTracker library:
- Download the .zip file from the releases section of GitHub
- In Arduino, select SKETCH>IMPORT LIBRARY...>ADD LIBRARY... and find the .zip file
- This will install the library in your My Documents (Windows) or Documents (Mac) folder under Arduino/libraries
- You can also unzip the file, and install it in the above libraries folder manually
- See arduino.cc/en/Guide/Libraries for more info on libraries

To upload the solar tracker optimizer routine to your arduino simply open `sketches/optimizer/optimizer.ino` in the arduino IDE and upload it.

To upload the skyread routine see `sketches/skyread/skyread.ino`, also try the live python plotting and recording under `sketches/skyread/python/skyread.py` .


Debugging
---
There are several tests present under the folder `tests` to confirm that your arduino and its components are working properly.


Expected pin ordering in current version
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

