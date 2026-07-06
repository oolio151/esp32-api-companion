#pragma once
#include <WebServer.h>

extern WebServer server;
extern String pinModes[];

void handleListPins();
void handleGetPin();
void handleSetMode();
void handleSetValue();
void handlePing();