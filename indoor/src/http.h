#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

struct APIResponse {
    bool success;
    int sleepDurationMilliseconds;
    int fanDutyCycle;
};

APIResponse postIndoor(float temp, float hum, bool window);