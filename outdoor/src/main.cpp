#include <ArduinoJson.h>

#include "aht.h"
#include "battery.h"
#include "http.h"
#include "wifi.h"

int update = 0;

void setup() {
    rst_info *resetInfo;
    resetInfo = ESP.getResetInfoPtr();
    Serial.begin(9600);
    Serial.println("");
    String reason;
    switch (resetInfo->reason) {
        case REASON_DEEP_SLEEP_AWAKE:
            reason = "Woke up from deep sleep!";
            break;
        case REASON_WDT_RST:
            reason = "Watchdog Timeout!";
            break;
        case REASON_SOFT_RESTART:
            reason = "Soft restart!";
            break;
        default:
            reason = "Unkown!";
            break;
    }
    Serial.println("Restarted because: " + reason);
    connectToWifi();
    delay(1000);
    checkAHT();
    checkWifiStatus();
    delay(1000);
    ESP.wdtEnable(WDTO_8S);
}

void loop() {
    ahtData aht = getAHTData();
    float battery = getBatteryPercentage();
    int sleep = 1000;
    if (update < 1) {
        APIResponse response = postOutdoor(aht.temp, aht.hum, battery);
        if (response.success) {
            sleep = response.sleepDurationMilliseconds;
            ESP.wdtFeed();
        } else {
            return;
        }
        if (sleep < 1000) {
            sleep = 1000;
        }
        Serial.printf("Deep Sleep for: %dms\n", sleep);
    } else {
        update--;
        ESP.wdtFeed();
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
