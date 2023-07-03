#include <ArduinoJson.h>

#include "aht.h"
#include "display.h"
#include "http.h"
#include "relay.h"
#include "wifi.h"
#include "window.h"

void setup() {
    // Display
    Serial.begin(9600);
    Serial.println("");
    setupRelay();
    connectToWifi();
    delay(1000);
    checkDisplay();
    setupDisplay();
    checkAHT();
    checkWifiStatus();
    ESP.wdtEnable(10000);
    delay(1000);
}

void loop() {
    AhtData aht = getAHTData();
    bool window = windowOpen();
    int sleep = 5000;  // default to 5 seconds
    APIResponse response = postIndoor(aht.temp, aht.hum, window);
    if (response.success) {
        sleep = response.sleepDurationMilliseconds;
        Serial.printf("FanDutyCycle: %d%%\n", response.fanDutyCycle);
        setRelay(response.fanDutyCycle > 0);
        if (sleep < 1000) {
            sleep = 1000;
        }
    }
    updateDisplay(aht.temp, aht.hum, window, getRelay());
    ESP.wdtFeed();
    Serial.printf("Waiting for: %dms\n", sleep);
    delay(sleep);
}
