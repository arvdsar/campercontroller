//CamperController (receiver with Relays)

#include <Arduino.h>
#include <Wire.h>
#include "SerialTransfer.h"

SerialTransfer myTransfer;
long timestamp = 0;

//Define 12v Relays
#define water_relay_pin 4
#define light1_relay_pin 5
#define light2_relay_pin 6
#define fridge_relay_pin 7
#define frost_relay_pin 8

//Define ADC for voltage & level sensors
#define startaccuvoltage_pin A0
#define hhaccuvoltage_pin A1
#define cleanwatersensor_pin A2
#define dirtwatersensor_pin A3

//init levels 
float startaccuvoltage = 12;
float hhaccuvoltage = 11.8;
int cleanwaterlevel = 80;
int dirtwaterlevel = 20;

//struct to be sent to CamperDisplay
struct dataSend
{
  int cleanwaterlevel;
  int dirtwaterlevel;
  float startaccuvoltage;
  float hhaccuvoltage;
} dataOutStruct;



//struct to be received by CamperController
struct dataReceived 
{
  int water_relay;
  int light1_relay;
  int light2_relay;
  int fridge_relay;
  int frost_relay;
} dataInStruct;


void setup() {
 Serial.begin(115200);
 Serial1.begin(19200);
 myTransfer.begin(Serial1);

//Set pins for relays to output
  pinMode(water_relay_pin, OUTPUT);
  pinMode(light1_relay_pin, OUTPUT);
  pinMode(light2_relay_pin, OUTPUT);
  pinMode(fridge_relay_pin, OUTPUT);
  pinMode(frost_relay_pin, OUTPUT);

//init all relays to OFF (assume HIGH means OFF)
  digitalWrite(water_relay_pin, HIGH); 
  digitalWrite(light1_relay_pin, HIGH);
  digitalWrite(light2_relay_pin, HIGH);
  digitalWrite(fridge_relay_pin, HIGH);
  digitalWrite(frost_relay_pin, HIGH);

}

void loop() {
  
  //collect and send data every 3 seconds to display
  // collect the data values from ADC logic

if(millis() > timestamp+500){
  Serial.println("Sending data");

  //this is dummy data for test
  dataOutStruct.startaccuvoltage = startaccuvoltage++;
  dataOutStruct.hhaccuvoltage = hhaccuvoltage++;
  dataOutStruct.cleanwaterlevel = cleanwaterlevel++;
  dataOutStruct.dirtwaterlevel = dirtwaterlevel++;

  //sent the data
  myTransfer.sendDatum(dataOutStruct); //sendDatum means only one data set. Check examples of serialtransfer.h
  Serial.println("DONE");
  timestamp = millis();
}

  //receive incomming messages
  //sending party determines frequency (at change or at least every 10 seconds or so)
  if(myTransfer.available())
  {
    myTransfer.rxObj(dataInStruct);

    //assume data is properly received. Then set the relays accordingly.
    digitalWrite(water_relay_pin, dataInStruct.water_relay); 
    digitalWrite(light1_relay_pin, dataInStruct.light1_relay);
    digitalWrite(light2_relay_pin, dataInStruct.light2_relay);
    digitalWrite(fridge_relay_pin, dataInStruct.fridge_relay);
    digitalWrite(frost_relay_pin, dataInStruct.frost_relay);
    
    Serial.print(dataInStruct.water_relay);
    Serial.print(dataInStruct.light1_relay);
    Serial.print(dataInStruct.light2_relay);
    Serial.print(dataInStruct.fridge_relay);
    Serial.print(dataInStruct.frost_relay);

  }


}