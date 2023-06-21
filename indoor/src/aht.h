#include <Adafruit_AHTX0.h>

struct AhtData {
    float temp;
    float hum;
};

void checkAHT();
AhtData getAHTData();