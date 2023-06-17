#include "aht.h"

// Sensor
Adafruit_AHTX0 aht;

void checkAHT() {
    Serial.print("Checking AHT...");
    if (!aht.begin()) {
        Serial.println("\nERROR: AHT not found!");
        while (1) {
            delay(1000);
        }
    } else {
        Serial.println("found!\n");
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