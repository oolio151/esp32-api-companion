#include "handlers.h"
#include "pins.h"
#include "json.h"
#include <ArduinoJson.h>

void handlePing() {
  server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleSetup() {
  server.on("/ping", HTTP_GET, handlePing);
  server.on("/pin", HTTP_GET, handleGetPin);
  server.begin();
  Serial.println("HTTP server started.");
}

void handleGetPin() {
  if (!server.hasArg("id")) {
    sendJsonError(400, "Missing 'id' parameter");
    return;
  }
  int pin = server.arg("id").toInt();

  JsonDocument doc;
  doc["pin"] = pin;
  doc["state"] = digitalRead(pin);
  sendJson(200, doc);
}