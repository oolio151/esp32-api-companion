#pragma once
#include <ArduinoJson.h>
#include <WebServer.h>

extern WebServer server;

void sendJson(int code, JsonDocument& doc) {
  String response;
  serializeJson(doc, response);
  server.send(code, "application/json", response);
}

void sendJsonError(int code, const char* message) {
  JsonDocument doc;
  doc["status"] = "error";
  doc["message"] = message;
  sendJson(code, doc);
}