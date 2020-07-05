// This program prints a photoresistors value to the serial monitor

int sensorPin = 2;  // digital pin to write HIGH too (attached to resistor but not the photoresistor)
int inputPin = 2;   // analog input pin from the high side of the photoresistor
int prValue;        // where the photoresistor value will be stored

void setup() {
    Serial.begin(9600);             // activate serial monitor
    pinMode(sensorPin, OUTPUT);     // set sensorPin to be output
    digitalWrite(sensorPin, HIGH);  // set sensorPin to HIGH
}

void loop() {
    Serial.print("Reading .... ");
    prValue = analogRead(inputPin); // Read value of the photoresistor
    Serial.println(prValue);        // Write the value to the serial monitor
    delay(1000);
}
