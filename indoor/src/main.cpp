#include <ArduinoJson.h>

#include "aht.h"
#include "display.h"
#include "http.h"
#include "wifi.h"
#include "window.h"

int update = 0;

void setup() {
    // Display
    Serial.begin(9600);
    Serial.println("");
    connectToWifi();
    delay(1000);
    checkDisplay();
    setupDisplay();
    checkAHT();
    checkWifiStatus();
    delay(1000);
}

void loop() {
    AhtData aht = getAHTData();
    updateDisplay(aht.temp, aht.hum);
    int sleep = 1000;
    if (update < 1) {
        APIResponse response = postIndoor(aht.temp, aht.hum, windowOpen());
        if (response.success) {
            sleep = response.sleepDurationMilliseconds;
            Serial.printf("FanDutyCycle: %d%%\n", response.fanDutyCycle);
        }
        Serial.printf("Waiting for: %dms\n", sleep);
    } else {
        update--;
    }
    delay(sleep);
}
