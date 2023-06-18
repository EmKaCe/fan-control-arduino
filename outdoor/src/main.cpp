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

String createPayload(float temp, float hum, float battery) {
    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp;
    doc["relativeHumidity"] = hum;
    doc["battery"] = battery;
    String payload;
    serializeJson(doc, payload);
    return payload;
}

void loop() {
    ahtData aht = getAHTData();
    float battery = getBatteryPercentage();
    if (update < 1) {
        String payload = createPayload(aht.temp, aht.hum, battery);
        if (sendData(payload) == 200) {
            // TODO: parse response
            update = 10;
        } else {
            delay(500);
        }
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
    delay(5000);
}
