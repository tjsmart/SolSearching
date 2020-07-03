#include "solarTracker.hpp"
#include <iostream>

int main(){
    int pins[] = {2, 3, 4, 5};
    int motors[] = {9, 10};
    
    solarTracker tracker(pins, motors);
    tracker.printResistorPins();

    int *test;
    test = tracker.getResistorPins();
    for (int i = 0; i < 4; i++)
    {
        std::cout << *(test + i) << std::endl;
    }


    tracker.printMotorPins();

    int *test2;
    test2 = tracker.getMotorPins();
    for (int i = 0; i < 2; i++)
    {
        std::cout << *(test2 + i) << std::endl;
    }

    return 0;
}
