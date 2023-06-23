#include <Arduino.h>

#ifndef RELAYPIN
#define RELAYPIN D3
#endif

void setupRelay();

void setRelay(boolean state);