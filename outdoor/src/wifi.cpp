#include "wifi.h"

// WiFi-Configuration
#ifndef STASSID
#define STASSID "SSID_HERE"
#define STAPSK "PASSWORD_HERE"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void connectToWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

void checkWifiStatus() {
    Serial.print("Connecting to WiFi: ");
    int times = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (times++ > 30) {
            Serial.println("\nCouldn't connect to WiFi\nPlease check connection!");
            while (true) {
                delay(1000000);
            }
        }
        delay(5000);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
}