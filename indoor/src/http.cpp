#include "http.h"

// API Configuration
// Address of API backend
String api = "10.42.0.1:3001"; // TODO: Change this with HTTPs

int sendData(String payload) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, "http://" + api + "/indoor");
    http.addHeader("Content-Type", "application/json");
    return http.POST(payload);
}