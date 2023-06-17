#include <Adafruit_AHTX0.h>

struct ahtData {
    float temp;
    float hum;
};

void checkAHT();
ahtData getAHTData();