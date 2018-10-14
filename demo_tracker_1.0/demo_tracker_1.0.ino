#include <VarSpeedServo.h>
//SOME NOTES ABOUT VARSPEEDSERVO
//attach(pin )  - Attaches a servo motor to an i/o pin.
//attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
//default min is 544, max is 2400  

//write(value)     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
//write(value, speed) - speed varies the speed of the move to new position 0=full speed, 1-255 slower to faster
//write(value, speed, wait) - wait is a boolean that, if true, causes the function call to block until move is complete

//writeMicroseconds() - Sets the servo pulse width in microseconds 
//read()      - Gets the last written servo pulse width as an angle between 0 and 180. 
//readMicroseconds()  - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
//attached()  - Returns true if there is a servo attached. 
//detach()    - Stops an attached servos from pulsing its i/o pin. 

//slowmove(value, speed) - The same as write(value, speed), retained for compatibility with Korman's version

//stop() - stops the servo at the current position

//sequencePlay(sequence, sequencePositions); // play a looping sequence starting at position 0
//sequencePlay(sequence, sequencePositions, loop, startPosition); // play sequence with number of positions, loop if true, start at position
//sequenceStop(); // stop sequence at current position
//wait(); // wait for movement to finish
//isMoving()  // return true if servo is still moving



VarSpeedServo hserv;          // create servo object to control a servo
VarSpeedServo vserv;         

int sensorTwo = 2;       //digital pin 2 connected to the resistor of first sensor
int sensorThree = 3;       //
int sensorFour = 4;
int sensorFive = 5;

int inputTwo = 2;        //variable to store the values from the analog pin 2
int inputThree = 3;       
int inputFour = 4;        
int inputFive = 5;        

int hpos = 85;        // variable to store the servo's horizontal position
int vpos = 92;        

int ledPin = 11;


int darkthres = 950; // defines how dark is dark
int hthres = 60; // threshold to define when to move horizontally
int vthres = 90; // threshold to define when to move vertically
int hmove = 1; // amount to move horizontal position
int vmove = 1; // amount to move vertical position
int rest_time = 1; // time to wait when the servo positions are good
int sleep_time = 2000; // time to wait when no light is present
int alpha=1; // play around with this
int beta=1; // play around with this

//add test comment
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
  hserv.attach(10);         // attaches the servo on pin 9 to the servo object
  vserv.attach(9);
  hserv.write(hpos,20,true);    // tell servo to go to position 'hpos' at speed 20
  vserv.write(vpos,20,true);    // tell servo to go to position 'vpos' at speed 20

  Serial.begin(9600);  //Begin serial communcation
  pinMode( ledPin, OUTPUT );
}
void loop()
{
  //Serial.println(2);
  Serial.println(analogRead(sensorTwo)); //Write the value of the photoresistor to the serial monitor.
  //Serial.println(3);
  Serial.println(analogRead(sensorThree));
  //Serial.println(4);
  Serial.println(analogRead(sensorFour));
  //Serial.println(5);
  Serial.println(analogRead(sensorFive));


  analogWrite(ledPin, analogRead(sensorTwo) / 1.5); 
  //send the value to the ledPin. Depending on value of resistor
  //you have  to divide the value. for example,
  //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
  delay(15); //short delay for faster response to light.



  int valueTwo = analogRead(inputTwo); //reads the value from ___ sensor
  int valueThree = analogRead(inputThree); //reads the value from the ___ sensor
  int valueFour = analogRead(inputFour); //reads the value from the ___ sensor
  int valueFive = analogRead(inputFive); //reads the value from the ___ sensor
  int diffv = valueTwo - valueThree;      //difference of two values from the sensors
  int diffh = valueFour - valueFive;      //difference of two values from the sensors



if (valueTwo < darkthres || valueThree < darkthres || valueFour < darkthres || valueFive < darkthres) //if light is present
  {
    if (diffh >= hthresh || diffh <= -hthresh)
      {
       hmove = alpha * diffh;          // need to define alpha -- a constant may work
       hpos = hpos + hmove;
       hserv.write(hpos,10,true);
      }
     if (diffv >= vthresh || diffv <= -vthresh)
      {
       vmove = beta * diffv;           // need to define beta -- a constant may work
       vpos = vpos + vmove;
       vserv.write(vpos,10,true);
      }

//    hserv.stop();
//    vserv.stop();
//    delay(rest_time);   // rest
  }
// else // well shit the sun is gone
//   {
//     vserv.write(85,20,true);
//     hserv.write(90,20,true);
//     delay(sleep_time);  // night night 
//   }
// 
}                            //end of void loop() method
