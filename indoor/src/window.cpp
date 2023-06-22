#include "window.h"

bool windowOpen() {
    return digitalRead(MC38PIN);
};