#include <VarSpeedServo.h>

// this version is untested!!!!!!!!!!!!!!! TODO

// create servo object -- methods described in "servo_info.txt"
VarSpeedServo hserv;
VarSpeedServo vserv;

// digital pins
int digitalPins[] = {2, 3, 4, 5};
// analog pins
int analogPins[] = {2, 3, 4, 5};
// led pin
int ledPin = 11;

// position, movement amount, speed, threshold to initiate movement, movement prefactor
// create servo movement class? TODO
int hpos = 85;
int hmove = 5;
int hspeed = 10;
int hthresh = 60;
int alpha = 1;
int hpin = 10;

int vpos = 62;
int vmove = 5;
int vspeed = 10;
int vthresh = 60;
int beta = 1;
int vspin = 9;

// other variables
int darkThresh = 1000; // defines how dark is dark
int delayTime = 10;    // time to wait when the servo positions are good
int sleepTime = 10;    // time to wait when no light is present

// photoresistor values:
//      analog[0], analog[1], analog[2], analog[3], analog[1] - analog[0], analog[3] - analog[2]
//      hdiff = analog[1] - analog[0] = PRValues[4]
//      vdiff = analog[3] - analog[2] = PRValues[5]
int PRValues[6];

void setup()
{
  // set digital pins as output and write high
  for (int i = 0; i < sizeof(digitalPins))
    ; i++)
  {
    pinMode(digitalPins[i], OUTPUT);
    digitalWrite(digitalPins[i], HIGH);
  }

  // attach pins to servo and write initial positions
  hserv.attach(hpin);
  vserv.attach(vpin);
  hserv.write(hpos, hspeed, true);
  vserv.write(vpos, vspeed, true);

  // begin serial communcation
  Serial.begin(9600);
  // set led pin
  pinMode(ledPin, OUTPUT);
}

void loop()
{

  // send the value to the ledPin. Depending on value of resistor
  // you have  to divide the value. for example,
  // with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
  analogWrite(ledPin, analogRead(sensorTwo) / 1.5);

  // read pins and store values in PRValues
  for (int i = 0; i < sizeof(analogPins); i++)
  {
    PRValues[i] = analogRead(analogPins[i]);
  }
  // hdiff
  PRValues[4] = PRValues[1] - PRValues[0];
  // vdiff
  PRValues[5] = PRValues[3] - PRValues[2];

  // uncomment this line to print PRValues to serial monitor
  // writePRValues();

  // this section determines how to move and applies it
  // if light is present
  if (valueTwo < darkThresh || valueThree < darkThresh || valueFour < darkThresh || valueFive < darkThresh)
  {
    // if source of light is unoptimized
    if (PRValues[4] >= hthresh || PRValues[5] >= vthresh || PRValues[4] <= hthresh || PRValues[5] <= vthresh)
    {

      // shouldn't these all be floats????? TODO
      hmove = PRValues[4] / 80;
      hpos = hpos + hmove;
      hserv.write(hpos, hspeed, true);

      vmove = PRValues[5] / 80;
      vpos = vpos + vmove;
      vserv.write(vpos, vspeed, true);

      Serial.print(hmove);
      Serial.print("\t");
      Serial.println(vmove);
    }
  }

  // delay time between loops
  delay(delayTime);
}

// user constructed methods defined below

void writePRValues()
{
  // this method writes photoresistor values to the serial monitor
  for (int i = 0; i < sizeof(PRValues))
    ; i++)
  {
    Serial.print(PRValues[i]);
    Serial.print("\t");
  }
  Serial.println();
}
