# Fan-Control-Arduino

This project includes code to communicate with the [fan-control-backend](https://github.com/U1F984/fan-control-backend).

## Prerequisites

### Hardware:
- WeMos D1 Mini
- SSD1306 (indoor)
- MC-38 (indoor)
- AHT10
- Li-Ion Battery (outdoor)

### Software:
- PlatformIO
- [adafruit/Adafruit AHTX0@^2.0.3](https://github.com/adafruit/Adafruit_AHTX0)
- [adafruit/Adafruit SSD1306@^2.5.7](https://github.com/adafruit/Adafruit_SSD1306) (indoor)
- [adafruit/Adafruit Unified Sensor@^1.1.9](https://github.com/adafruit/Adafruit_Sensor)
- [bblanchon/ArduinoJson@^6.21.2](https://github.com/bblanchon/ArduinoJson)
- [adafruit/Adafruit GFX Library@^1.11.5](https://github.com/adafruit/Adafruit-GFX-Library) (indoor)


## Configuration

### Display (indoor only)

1. Open [display.cpp](/indoor/src/display.cpp).
2. Configure the `Display setup` section according to your display.
3. You might wish to change the `AUTHOR` definition as well.

### MC-38 (indoor only)

1. Open [window.h](/indoor/src/window.h)
2. Change `#define MC38PIN D4` according to your pin (Default: D4)

### HTTP

1. Open the [indoor http.cpp](/indoor/src/http.cpp) or [outdoor http.cpp](/outdoor/src/http.cpp) respectively.
2. Change the `api` string according to the hostname of your backend.

### WiFi
1. Open the [indoor wifi.cpp](/indoor/src/wifi.cpp) or [outdoor wifi.cpp](/outdoor/src/wifi.cpp) respectively.
2. Change `"SSID_HERE"` and `"PASSWORD_HERE"` to your WiFi credentials accordingly.

### Battery (outdoor only)
1. Open [battery.cpp](/outdoor/src/battery.cpp).
2. Change `maxVoltage` according to the maximum output voltage.
3. Change `minVoltage` according to the cutoff voltage.
4. Adjust `calibration` based on dropout voltage.