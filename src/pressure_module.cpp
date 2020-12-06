#include <Arduino.h>
#include "sensors_module.h"

#define pressure_sensor_AI 35

int pressure_raw; // A/D reading of pressure sensor
int pressure_zero = 208; // A/D at atmospheric pressure
int pressure_max = 922; // A/D at max pressure
float pressure_bar; // final pressure in bars

void setup_pressure_sensor()
{
}

float read_pressure_bar()
{
  pressure_raw = analogRead(pressure_sensor_AI);
  pressure_bar = ((pressure_raw - pressure_zero) * 1.2 / (pressure_max - pressure_zero)) * 10.0;

  return pressure_raw;
}