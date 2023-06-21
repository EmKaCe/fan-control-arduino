#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

struct APIResponse {
    bool success;
    int sleepDurationMilliseconds;
};

APIResponse postOutdoor(float temp, float hum, float battery);