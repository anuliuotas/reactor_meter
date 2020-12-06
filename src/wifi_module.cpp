
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include <wifi_module.h>
#include <current_readings.h>

// Set web server port number to 80
AsyncWebServer server(80);

// Variable to store the HTTP request
String header;

String generate_reading();
String get_current_pressure_reading_bar();
String get_current_temperature_reading_celsius();
String get_current_ph_reading();
String get_current_state();

const char* ssid     = "Raspberry";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "raspberry";
const bool ap_mode = false;

void setup_wifi_module() {

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
  }

  if (ap_mode) {
    Serial.println("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  } else {
    WiFi.begin(ssid, password);
    delay(1000);
    check_connection_status();
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", get_current_temperature_reading_celsius().c_str());
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });
  server.on("/acidity", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", get_current_ph_reading().c_str());
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", get_current_pressure_reading_bar().c_str());
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });

  server.begin();
}

String get_current_pressure_reading_bar() {
    return String(current_pressure_reading_bar);
}

String get_current_temperature_reading_celsius() {
    return String(current_temperature_reading_celsius);
}

String get_current_ph_reading() {
    return String(current_ph_reading);
}



void check_connection_status() {
  if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting to WiFi. ");
  }
  if(WiFi.status() == WL_CONNECTED) {
    //If connection successful show IP address in serial monitor
    Serial.print("Connected to ");
    Serial.print(ssid);
    Serial.print(". IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
    wifi_connected = 1;
  } else {
    wifi_connected = 0;
  }
}


String generate_reading() {
  // Read temperature as Celsius (the default)
  float t = random(5, 10);
  if (isnan(t)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    return String(t);
  }
}
