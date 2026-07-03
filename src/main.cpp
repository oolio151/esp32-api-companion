#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>   // https://github.com/tzapu/WiFiManagerv if you need the docs
#include <WebServer.h>
#include <ArduinoJson.h>
#include "pins.h"

WebServer server(80);


void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFiManager wm;

  // wm.resetSettings();

  bool connected = wm.autoConnect("ESP32-Setup");

  if (!connected) {
    Serial.println("Failed to connect and hit timeout");
    ESP.restart();
  }

  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(1000);
}