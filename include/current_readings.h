#ifndef CURRENT_READINGS
#define CURRENT_READINGS

#include <Arduino.h>

#include <ThreeWire.h>  
#include <RtcDS1302.h>

extern float current_pressure_reading_bar;
extern float current_temperature_reading_celsius;
extern float current_ph_reading;
extern RtcDateTime current_system_time;
extern int wifi_connected;

#endif
