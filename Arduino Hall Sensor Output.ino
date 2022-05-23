#include <SoftwareSerial.h>

//Constants
float Tuning = 568.5;
float FilamentSize = 1.75;

//Analog pins
float AnalogPin0;
float AnalogPin1;

//Variables
float AnalogAvg;
float FilamentCalc;
float FilamentPercent;

//Serial Transmit Pin
////Recieve = pin 0
////Transmit = pin 1
SoftwareSerial NANOserial(1,2);

//SETUP
void setup()
{
Serial.begin(34000);
//Serial.print("RX TX Serial Established at 34000...");
//Serial.println();
}

//MAIN LOOP
void loop()
{
//Calculate Filament Size
AnalogPin0 = analogRead(0);
AnalogPin1 = analogRead(1);
AnalogAvg = (AnalogPin0 + AnalogPin1) / 2;
FilamentCalc = (FilamentSize / AnalogAvg) * Tuning;
FilamentPercent = (FilamentSize / FilamentCalc) * 100;

//Print to Serial
Serial.print("\a");               //Begin marker
Serial.print(FilamentPercent, 6); //6 decimal places
Serial.println();

delay(500); 
}
