#pragma once
#include <WebServer.h>

extern WebServer server;
extern String pinModes[];
extern int8_t pinsInUse[];

void handleListPins();
void handleGetPin();
void handleSetMode();
void handleSetValue();
void handlePing();
void handleSetup();