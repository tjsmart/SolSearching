#include <VarSpeedServo.h>
#include "setup.hpp"

// instatiate two servos
// for more info see https://github.com/netlabtoolkit/VarSpeedServo/blob/master/VarSpeedServo.cpp
VarSpeedServo hserv;
VarSpeedServo vserv;         


void setup()
{
    pinMode(sensorTwo, OUTPUT);  //initialize the digital pin as output
    pinMode(sensorThree, OUTPUT);  
    pinMode(sensorFour, OUTPUT);  
    pinMode(sensorFive, OUTPUT);
    digitalWrite(sensorTwo, HIGH);
    digitalWrite(sensorThree, HIGH);
    digitalWrite(sensorFour, HIGH);
    digitalWrite(sensorFive, HIGH);
    hserv.attach(hservoPin);         // attaches the servo on pin 9 to the servo object
    vserv.attach(vservoPin);
    hserv.write(hpos,10,true);    // tell servo to go to position 'hpos' at speed 20
    vserv.write(vpos,10,true);    // tell servo to go to position 'vpos' at speed 20

    Serial.begin(9600);  //Begin serial communcation
}


void loop()
{

    int valueTwo = analogRead(inputTwo); //reads the value from ___ sensor
    int valueThree = analogRead(inputThree); //reads the value from the ___ sensor
    int valueFour = analogRead(inputFour); //reads the value from the ___ sensor
    int valueFive = analogRead(inputFive); //reads the value from the ___ sensor
    int diffh = valueThree - valueTwo;      //difference of two values from the sensors
    int diffv = valueFive - valueFour;      //difference of two values from the sensors

    Serial.print(valueTwo); //Write the value of the photoresistor to the serial monitor.
    Serial.print("\t");
    Serial.print(valueThree);
    Serial.print("\t");
    Serial.print(diffh);
    Serial.print("\t");
    Serial.print(valueFour);
    Serial.print("\t");
    Serial.print(valueFive);
    Serial.print("\t");
    Serial.println(diffv);


    //if light is present
    if (valueTwo < darkthres || valueThree < darkthres || valueFour < darkthres || valueFive < darkthres){
        //if light source is unoptimized
        if (diffh >= hthres || diffv >= vthres || diffh <= hthres || diffv <= diffv){
            hmove = diffh/100;
            hpos = hpos + hmove;
            hserv.write(hpos,10,true);
            vmove = diffv/100;
            vpos = vpos + vmove;
            vserv.write(vpos,10,true);
            Serial.print(hmove);
            Serial.print("\t");
            Serial.println(vmove);
        }
        else{
            //sleep
            delay(rest_time);
        }
    }
    else{
        //big sleep?
        delay(sleep_time);
    }

}
