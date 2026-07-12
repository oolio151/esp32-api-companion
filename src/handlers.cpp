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
  server.on("/mode", HTTP_POST, handleSetPinState);
  server.on("/set-d", HTTP_POST, handleSetPinValueDigital);
  server.begin();
  Serial.println("HTTP server started.");
}

void handleGetPin() {
  if (!server.hasArg("pin")) {
    sendJsonError(400, "Missing 'pin' parameter");
    return;
  }
  int pin = server.arg("pin").toInt();

  if (!isValidPin(pin, PinType::DIGITAL) && pinsInUse[pin] != 0 && pinsInUse[pin] != -1) {
    sendJsonError(400, "Invalid pin number or pin not configured");
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

void handleSetPinValueDigital() {
  if (!server.hasArg("pin") || !server.hasArg("value")) {
    sendJsonError(400, "Missing 1 or more parameter(s)");
    return;
  }

  int pin = server.arg("pin").toInt();

  if (!isValidPin(pin, PinType::DIGITAL) || pinsInUse[pin] != 2) {
    sendJsonError(400, "Either the pin number is invalid or the pin is not set as an OUTPUT pin");
    return;
  }

  int value = server.arg("value").toInt();

  if (value != 1 && value != 0) {
    sendJsonError(400, "Can only write 0 or 1 to digital pins");
    return;
  }
  
  digitalWrite(pin, value);

  JsonDocument doc;
  doc["status"] = "success";
  doc["pin"] = pin;
  doc["value"] = value;
  sendJson(200, doc);
}