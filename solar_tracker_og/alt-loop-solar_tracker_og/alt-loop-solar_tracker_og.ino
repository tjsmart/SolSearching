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
  Serial.println(1);
  Serial.println(analogRead(sensorTwo)); //Write the value of the photoresistor to the serial monitor.
  Serial.println(2);
  Serial.println(analogRead(sensorThree));
  Serial.println(3);
  Serial.println(analogRead(sensorFour));
  Serial.println(4);
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


//This is the actual tracking loop, we need to find a way to run this once right away, and then
//go into a mode where it only wakes up and runs the loop every minute or two from then on.
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

// with this version the loop will have 9 possible conditions: r&t, r&b, l&t, l&b, r, l, t, b, none. Where r=right, l=left, t=top, b=bottom
// the benefit of this is that it should use both servos simultaneously -- should (slighltly) improve speed
//
// it may be beficial to set up values such as:
// int darkthres = 950; // defines how dark is dark
// int servo_move_time = 10; // time to wait for servos to move
// int hthres = 200; // threshold to define when to move horizontally
// int vthres = 100; // threshold to define when to move vertically
// int hmove = 5; // amount to move horizontal position
// int vmove = 5; // amount to move vertical position
// int correct_time = 100; // time to wait when the servo positions are good
// int rest_time = 1000; // time to wait when no light is present


if (valueTwo < 950 || valueThree < 950) //if light is present
  {
      if (diffh >= 200 && diffv >= 100)             //if light source is towards right & top
      {
      currhorizontalPos = currhorizontalPos + 5;      // appropriately update 'pos'
      myhorizontalservo.write(currhorizontalPos);     // tell servo to go to position in variable 'pos'
      currverticalPos = currverticalPos + 5;
      myverticalservo.write(currverticalPos);
      delay(10);                 // waits 30ms for the servo to reach the position
      }
      else if (diffh >= 200 && diffv <= -100)             //if light source is towards right & bottom
      {
      currhorizontalPos = currhorizontalPos + 5;
      myhorizontalservo.write(currhorizontalPos);
      currverticalPos = currverticalPos - 5;
      myverticalservo.write(currverticalPos);
      delay(10);
      }
      else if (diffh <= -200 && diffv >= 100)             //if light source is towards left & top
      {
      currhorizontalPos = currhorizontalPos - 5;
      myhorizontalservo.write(currhorizontalPos);
      currverticalPos = currverticalPos + 5;
      myverticalservo.write(currverticalPos);
      delay(10);
      }
      else if (diffh <= -200 && diffv <= -100)             //if light source is towards left & bottom
      {
      currhorizontalPos = currhorizontalPos - 5;
      myhorizontalservo.write(currhorizontalPos);
      currverticalPos = currverticalPos - 5;
      myverticalservo.write(currverticalPos);
      delay(10);
      }
      else if (diffh >= 200 )             //if light source is towards right only
      {
      currhorizontalPos = currhorizontalPos + 5;
      myhorizontalservo.write(currhorizontalPos);
      delay(10);
      }
      else if (diffh <= -200 )             //if light source is towards left only
      {
      currhorizontalPos = currhorizontalPos - 5;
      myhorizontalservo.write(currhorizontalPos);
      delay(10);
      }
      else if (diffv >= 100 )             //if light source is towards top only
      {
      currverticalPos = currverticalPos + 5;
      myverticalservo.write(currverticalPos);
      delay(10);
      }
      else if (diffv <= -100 )             //if light source is towards bottom only
      {
      currverticalPos = currverticalPos - 5;
      myverticalservo.write(currverticalPos);
      delay(10);
      }
      else                                 // position is good now
      {
      delay(100);                          // rest
      }
  }
  else                                     // well shit the sun is gone
  {
    delay(1000);                           // what do we want it do when it is dark??
  }

}                            //end of void loop() method
