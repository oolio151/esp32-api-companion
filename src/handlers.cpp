#include "handlers.h"
#include "pins.h"
#include <ArduinoJson.h>

void handlePing() {
  server.send(200, "application/json", "{\"status\":\"ok\"}");
}