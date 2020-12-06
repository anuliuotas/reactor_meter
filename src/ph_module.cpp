#include <Arduino.h>
#include "sensors_module.h"

#define ph_sensor_AI 25

int ph_raw; // A/D reading of ph sensor
int ph_zero = 101; // A/D at atmospheric ph
int ph_max = 922; // A/D at max ph
float ph_final; // final ph
int ph_7 = 912;

void setup_ph_sensor()
{
}

float read_ph()
{
  ph_raw = analogRead(ph_sensor_AI);
  ph_final = ((ph_raw - ph_zero) * 1.2 / (ph_max - ph_zero)) * 10.0;

  return ph_raw;
}