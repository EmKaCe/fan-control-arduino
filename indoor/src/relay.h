#include <Arduino.h>

#ifndef RELAYPIN
#define RELAYPIN D3
#endif

void setupRelay();

bool getRelay();
void setRelay(boolean state);