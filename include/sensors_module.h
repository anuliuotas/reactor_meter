#ifndef SENSORS_MODULE
#define SENSORS_MODULE

void setup_temperature_sensor();
void setup_pressure_sensor();
void setup_ph_sensor();

float read_temperature_celsius();
float read_pressure_bar();
float read_ph();

#endif