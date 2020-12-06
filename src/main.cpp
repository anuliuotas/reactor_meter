#include <Arduino.h>

#include "sensors_module.h"
#include "wifi_module.h"
#include "current_readings.h"

#include "Ticker.h"

void updateSensorReadings();
void logCurrentState();
void updateWifiStatus();
void updateLedState();

Ticker timer1(updateSensorReadings, 1000);
Ticker timer2(logCurrentState, 1000);
Ticker timer3(updateWifiStatus, 10000);
Ticker timer4(updateLedState, 1000);

const int ticker_count = 4;
Ticker tickers[ticker_count] = {timer1, timer2, timer3, timer4};

const int wifi_led_pin = 2;
const int power_led_pin = 15;

void setup() {
  Serial.begin(9600);
  pinMode(wifi_led_pin, OUTPUT);
  pinMode(power_led_pin, OUTPUT);
  digitalWrite(power_led_pin, HIGH);
  setup_wifi_module();

  for(int i = 0; i < ticker_count; i++) {
    tickers[i].start();
  }
}

void updateWifiStatus() {
  check_connection_status();
}

void updateSensorReadings() {
  current_pressure_reading_bar = read_pressure_bar();
  current_temperature_reading_celsius = read_temperature_celsius();
  current_ph_reading = read_ph();
}

void logCurrentState() {
  Serial.print("Temperature: ");
  Serial.print(current_temperature_reading_celsius);
  Serial.print(" C, ");
  Serial.print(": ");
  Serial.print("Pressure: ");
  Serial.print(current_pressure_reading_bar);
  Serial.print(" bar");
  Serial.print(", ");
  Serial.print("Acidity: ");
  Serial.print(current_ph_reading);
  Serial.println(" ph");
}

int led_state = 0;
void updateLedState() {
  if(wifi_connected == 0) {
    if (led_state == 1) {
      led_state = 0;
    } else {
      led_state = 1;
    }
  } else {
    led_state = 1;
  }
  Serial.print("Led state: ");
  Serial.println(led_state);

  if(led_state == 1) {
    digitalWrite(wifi_led_pin, HIGH);
  } else {
    digitalWrite(wifi_led_pin, LOW);
  }
}

void loop() {
  for(int i = 0; i < ticker_count; i++) {
    tickers[i].update();
  }
}

