/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "max6675.h"
#include "sensors_module.h"

// Data wire is conntec to the Arduino digital pin 32
#define ONE_WIRE_BUS 32

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup_temperature_sensor()
{
  // Start up the library
  sensors.begin();
}

float read_temperature_celsius(){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 

  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  float temp_c = sensors.getTempCByIndex(0);
  return temp_c;
}