#include <Servo.h>
Servo hserv;          // create servo object to control a servo
Servo vserv;         

int sensorTwo = 2;       //digital pin 2 connected to the resistor of first sensor
int sensorThree = 3;       //
int sensorFour = 4;
int sensorFive = 5;

int inputTwo = 2;        //variable to store the values from the analog pin 2
int inputThree = 3;       
int inputFour = 4;        
int inputFive = 5;        

int hpos = 100;        // variable to store the servo's horizontal position
int vpos = 100;        

int ledPin = 11;


int darkthres = 950; // defines how dark is dark
int servo_move_time = 10; // time to wait for servos to move
int hthres = 200; // threshold to define when to move horizontally
int vthres = 100; // threshold to define when to move vertically
int hmove = 5; // amount to move horizontal position
int vmove = 5; // amount to move vertical position
int rest_time = 100; // time to wait when the servo positions are good
int sleep_time = 1000; // time to wait when no light is present

int alpha = 0.1;  // proportionality constant for diffh and hmove
int beta = 0.1;   // proportionality constant for diffv and vmove

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
  hserv.write(hpos);    // tell servo to go to position in variable 'pos'
  vserv.write(vpos);    // tell servo to go to position in variable 'pos'

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


  analogWrite(ledPin, analogRead(sensorTwo) / 1.5); 
  //send the value to the ledPin. Depending on value of resistor
  //you have  to divide the value. for example,
  //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
  delay(15); //short delay for faster response to light.



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


if (valueTwo < darkthres || valueThree < darkthres || valueFour < darkthres || valueFive < darkthres) //if light is present
  {
    while (abs(diffh) >= hthres || abs(diffv) >= vthres)    // as long as diffh or diffv are above the thresholds ( in this case the thresholds should be really small and need not change )
    {
    hmove = alpha * diffh;          // need to define alpha -- a constant may work
    hpos = hpos + hmove;
    hserv.write(hpos);
    vmove = beta * diffv;           // need to define beta -- a constant may work
    vpos = vpos + vmove;
    vserv.write(vpos);
    delay(servo_move_time); 
    }
    // position is good now
    //hserv.stop();
    //vserv.stop();
    delay(rest_time);   // rest
  }
else // well shit the sun is gone
  {
    //vserv.write(85,20,true);
    //hserv.write(90,20,true);
    delay(sleep_time);  // night night 
  }

}                            //end of void loop() method
