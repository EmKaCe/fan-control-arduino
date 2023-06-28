#include "http.h"

// API Configuration
// Hostname of API backend
String api = "10.42.0.1:3002";

APIResponse postOutdoor(float temp, float hum, float battery) {
    int code = -1;
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    {
        String payload;
        {
            DynamicJsonDocument doc(80);
            doc["temperature"] = temp;
            doc["relativeHumidity"] = hum;
            doc["battery"] = battery;
            serializeJson(doc, payload);
        }
        https.begin(*client, "https://" + api + "/outdoor");
        https.addHeader("Content-Type", "application/json");
        code = https.POST(payload);
    }

    APIResponse data;
    data.success = code == HTTP_CODE_OK;
    if (data.success) {
        DynamicJsonDocument doc(https.getSize() + 20);
        {
            const String& payload = https.getString();
            deserializeJson(doc, payload);
            https.end();
        }
        data.sleepDurationMilliseconds = doc["sleepDurationMilliseconds"].as<int>();
    }
    return data;
};