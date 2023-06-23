#include "relay.h"

void setupRelay() {
    pinMode(RELAYPIN, OUTPUT);
}

void setRelay(boolean state) {
    digitalWrite(RELAYPIN, state);
};