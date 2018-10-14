#include <Servo.h>
Servo myhorizontalservo;          // create servo object to control a servo
Servo myverticalservo;         

int sensorTwo = 2;       //digital pin 2 connected to the resistor of first sensor
int sensorThree = 3;       //
int sensorFour = 4;
int sensorFive = 5;

int inputTwo = 2;        //variable to store the values from the analog pin 2
int inputThree = 3;       
int inputFour = 4;        
int inputFive = 5;        

int currhorizontalPos = 100;        // variable to store the servo's horizontal position
int currverticalPos = 100;        

int ledPin = 11;
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
  myhorizontalservo.attach(9);         // attaches the servo on pin 9 to the servo object
  myverticalservo.attach(10);
  myhorizontalservo.write(currhorizontalPos);    // tell servo to go to position in variable 'pos'
  myverticalservo.write(currverticalPos);    // tell servo to go to position in variable 'pos'

  Serial.begin(9600);  //Begin serial communcation
  pinMode( ledPin, OUTPUT );
}
void loop()
{
  Serial.println(2);
  Serial.println(analogRead(sensorTwo)); //Write the value of the photoresistor to the serial monitor.
  Serial.println(3);
  Serial.println(analogRead(sensorThree));
  Serial.println(4);
  Serial.println(analogRead(sensorFour));
  Serial.println(5);
  Serial.println(analogRead(sensorFive));


  analogWrite(ledPin, analogRead(sensorTwo) / 2); 
  //send the value to the ledPin. Depending on value of resistor
  //you have  to divide the value. for example,
  //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
  delay(1000); //short delay for faster response to light.



  int valueTwo = analogRead(inputTwo); //reads the value from ___ sensor
  int valueThree = analogRead(inputThree); //reads the value from the ___ sensor
  int valueFour = analogRead(inputFour); //reads the value from the ___ sensor
  int valueFive = analogRead(inputFive); //reads the value from the ___ sensor
  int diffh = valueTwo - valueThree;      //difference of two values from the sensors
  int diffv = valueFour - valueFive;      //difference of two values from the sensors

  Serial.println(diffh);
  Serial.println(diffv);


//This is the actual tracking loop, we need to find a way to run this once right away, and then
//go into a mode where it only wakes up and runs the loop every minute or two from then on.
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

  if (valueTwo < 1000 || valueThree < 1000) //if light is present
   
  {
    if (diffh >= 200)             //if light source is towards right
    {
      currhorizontalPos = currhorizontalPos + 5;
      myhorizontalservo.write(currhorizontalPos);     // tell servo to go to position in variable 'pos'
      delay(10);                 // waits 30ms for the servo to reach the position
    }
    else if (diffh <= -200)           //if light source is towards left
    {
      currhorizontalPos = currhorizontalPos - 5;
      myhorizontalservo.write(currhorizontalPos);     // tell servo to go to position in variable 'pos'
      delay(10);                // waits 30ms for the servo to reach the position

    }
    else          //if light source is center
    {
      delay(10);                // waits 30ms ---> if this condition is met then h position is good ,, how large should delay be?

    }                            //end of inner if block

    if (diffv >= 100)             //if light source is towards top ---> with this current setup I believe it will take turns moving servos... can we do it simultaneously?
    {
      currverticalPos = currverticalPos + 5;
      myverticalservo.write(currverticalPos);     // tell vertical servo to go to position in variable 'pos'
      delay(10);                 // waits 30ms for the servo to reach the position
    }
    else if (diffv <= -100)           //if light source is towards bottom
    {
      currverticalPos = currverticalPos - 5;
      myverticalservo.write(currverticalPos);     // tell servo to go to position in variable 'pos'
      delay(10);                // waits 30ms for the servo to reach the position

    }                            //end of inner if block
    else          //if light source is center
    {
      delay(1000);                // waits 30ms ---> if this condition is met then v position is good ,, how large should delay be?

    }                            //end of inner if block
  }                           //end of main if block

}                            //end of void loop() method
