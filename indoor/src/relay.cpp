#include "relay.h"

void setupRelay() {
    pinMode(RELAYPIN, OUTPUT);
}

bool getRelay() {
    return digitalRead(RELAYPIN);
};

void setRelay(boolean state) {
    digitalWrite(RELAYPIN, state);
};