#include "http.h"

// API Configuration
// Hostname of API backend
String api = "10.42.0.1:8080";

APIResponse postOutdoor(float temp, float hum, float battery) {
    int code = -1;
    WiFiClient client;
    HTTPClient http;
    {
        String payload;
        {
            DynamicJsonDocument doc(80);
            doc["temperature"] = temp;
            doc["relativeHumidity"] = hum;
            doc["battery"] = battery;
            serializeJson(doc, payload);
        }
        http.begin(client, "http://" + api + "/outdoor"); // TODO: Change this with HTTPs
        http.addHeader("Content-Type", "application/json");
        code = http.POST(payload);
    }

    APIResponse data;
    data.success = code == HTTP_CODE_OK;
    if (data.success) {
        DynamicJsonDocument doc(http.getSize());
        {
            const String& payload = http.getString();
            deserializeJson(doc, payload);
            http.end();
        }
        data.sleepDurationMilliseconds = doc["sleepDurationMilliseconds"].as<int>();
    }
    return data;
};