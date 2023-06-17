#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Fonts/Org_01.h"

void checkDisplay();
void setupDisplay();
void updateDisplay(float temp, float hum);
void displayMessage(String message);