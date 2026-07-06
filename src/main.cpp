#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>   // https://github.com/tzapu/WiFiManager if you need the docs
#include <WebServer.h>
#include <ArduinoJson.h>

#include "pins.h"
#include "handlers.h"


WebServer server(80);

int8_t pinsInUse[40] = {0}; // 0 means not in use, 1 means in use, -1 means unsafe

void setup() {
  for (int pin : unsafePins) pinsInUse[pin] = -1;

  Serial.begin(115200);
  delay(1000);

  WiFiManager wm;

  // wm.resetSettings(); // uncomment for testing

  bool connected = wm.autoConnect("ESP32-Setup");

  if (!connected) {
    Serial.println("Failed to connect and hit timeout");
    //ESP.restart();
  } else {
    Serial.println("Connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/ping", HTTP_GET, handlePing);
    server.begin();
    Serial.println("HTTP server started.");
  }

  


}

void loop() {
  server.handleClient();
}

