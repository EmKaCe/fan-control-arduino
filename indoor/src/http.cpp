#include "http.h"

// API Configuration
// Hostname of API backend
String api = "10.42.0.1:3002";

APIResponse postIndoor(float temp, float hum, bool window) {
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
            doc["windowOpen"] = window;
            serializeJson(doc, payload);
        }
        https.begin(*client, "https://" + api + "/indoor");
        https.addHeader("Content-Type", "application/json");
        code = https.POST(payload);
    }
    APIResponse data;
    data.success = code == HTTP_CODE_OK;
    if (data.success) {
        DynamicJsonDocument doc(512);
        {
            const String& payload = https.getString();
            deserializeJson(doc, payload);
            https.end();
        }
        data.sleepDurationMilliseconds = doc["sleepDurationMilliseconds"].as<int>();
        data.fanDutyCycle = doc["fanDutyCycle"].as<int>();
    }
    return data;
};