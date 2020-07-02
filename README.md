SolSearching Repository
===

Getting started
---

There are several tests present under the folder `tests` to confirm that your arduino and its components are working properly.

To upload the solar tracker code to your arduino simply open `solar_tracker/solar_tracker.ino` in the arduino IDE and upload it.


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

