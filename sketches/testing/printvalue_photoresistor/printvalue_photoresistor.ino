// This program prints a photoresistors value to the serial monitor

int pin[] = {5, 2, 3, 4};
int prValue[4];        // where the photoresistor value will be stored

//int sensorPin = 1;  // digital pin to write HIGH too (attached to resistor but not the photoresistor)
//int inputPin = 1;   // analog input pin from the high side of the photoresistor
//int prValue;        // where the photoresistor value will be stored


void setup() {
    Serial.begin(9600);             // activate serial monitor

    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);     // set sensorPin to be output
        digitalWrite(pin[i], HIGH);  // set sensorPin to HIGH
    }
 
}

void loop() {
    Serial.print("Reading .... ");

    for (int i = 0; i < 4; i++)
    {
        prValue[i] = analogRead(pin[i]); // Read value of the photoresistor
        Serial.print(pin[i]);
        Serial.print(" = ");
        Serial.print(prValue[i]);        // Write the value to the serial monitor
        if (i != 3) Serial.print(" , ");
    }
    Serial.println();
    delay(1000);
}
