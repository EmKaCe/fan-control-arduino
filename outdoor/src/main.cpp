#include <ArduinoJson.h>

#include "aht.h"
#include "battery.h"
#include "http.h"
#include "wifi.h"

int update = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("");
    connectToWifi();
    delay(1000);
    checkAHT();
    checkWifiStatus();
    delay(1000);
}

void loop() {
    ahtData aht = getAHTData();
    float battery = getBatteryPercentage();
    int sleep = 1000;
    if (update < 1) {
        APIResponse response = postOutdoor(aht.temp, aht.hum, battery);
        if (response.success) {
            sleep = response.sleepDurationMilliseconds;
        }
        Serial.printf("Deep Sleep for: %dms\n", sleep);
    } else {
        update--;
    }
    Serial.println("");
    Serial.printf("Temperature: %.2f˚C", aht.temp);
    Serial.println("");
    Serial.printf("Rel. humidity: %.2f%%", aht.hum);
    Serial.println("");
    Serial.printf("Battery: %.2f%%", battery);
    Serial.println("");
    Serial.println("-----------");
    ESP.deepSleep(sleep * 1000);
}
