#include "aht.h"
#include "display.h"

// Sensor
Adafruit_AHTX0 aht;

void checkAHT() {
    displayMessage("Checking AHT...");
    if (!aht.begin()) {
        displayMessage("\nERROR: AHT not found!\n");
        while (1) {
            delay(1000);
        }
    } else {
        displayMessage("found!\n\n");
    }
}

ahtData getAHTData() {
    ahtData data;
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    data.hum = humidity.relative_humidity;
    data.temp = temp.temperature;
    return data;
}