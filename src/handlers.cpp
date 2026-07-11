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

  if (!isValidPin(pin, PinType::DIGITAL)) {
    sendJsonError(400, "Invalid pin number");
    return;
  }

  JsonDocument doc;
  doc["pin"] = pin;
  doc["state"] = digitalRead(pin);
  sendJson(200, doc);
}

void handleSetPinState() {
  if (!server.hasArg("mode") || !server.hasArg("id")) {
    sendJsonError(400, "Missing 1 or more parameter(s)");
    return;
  }

  int pin = server.arg("id").toInt();

  if (!isValidPin(pin, PinType::DIGITAL)) {
    sendJsonError(400, "Invalid pin number");
    return;
  }

  String mode = server.arg("mode");
  if (mode == "input"){
    pinMode(pin, INPUT);
    pinsInUse[pin] = 1;
  }
  else if (mode == "output") {
    pinMode(pin, OUTPUT);
    pinsInUse[pin] = 2;
  }
  else {
    sendJsonError(400, "Pin mode can only be \"input\" or \"output\"");
    return;
  }
  
  JsonDocument doc;
  doc["status"] = "success";
  doc["pin"] = pin;
  doc["mode"] = mode;
  sendJson(200, doc);
}