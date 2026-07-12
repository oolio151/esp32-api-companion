#pragma once
#include <WebServer.h>

extern WebServer server;
extern String pinModes[];
extern int8_t pinsInUse[];

void handleListPins();
void handleGetPin();
void handleSetValue();
void handlePing();
void handleSetup();
void handleSetPinState();
void handleSetPinValueDigital();