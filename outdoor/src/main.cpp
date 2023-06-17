#include <ArduinoJson.h>

#include "aht.h"
#include "http.h"
#include "wifi.h"

int update = 0;

void setup() {
    // Display
    Serial.begin(9600);
    Serial.println("");
    connectToWifi();
    delay(1000);
    checkAHT();
    checkWifiStatus();
    delay(1000);
}

String createPayload(float temp, float hum) {
    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp;
    doc["relativeHumidity"] = hum;
    String payload;
    serializeJson(doc, payload);
    return payload;
}

void loop() {
    ahtData aht = getAHTData();
    if (update < 1) {
        String payload = createPayload(aht.temp, aht.hum);
        if (sendData(payload) == 200) {
            // TODO: parse response
            update = 10;
        } else {
            delay(500);
        }
    } else {
        update--;
    }
    delay(1000);
}
