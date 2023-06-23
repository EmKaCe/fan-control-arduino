#include "display.h"

#define AUTHOR "Emre Cetin"

// Display setup
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void checkDisplay() {
    Serial.println("");
    Serial.print("Checking Display...");
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();
    Serial.println("Success!");
}

void setupDisplay() {
    Serial.print("Drawing Boot Screen...");
    display.fillCircle(90, 25, 17, 1);
    display.fillCircle(40, 25, 17, 1);
    display.fillCircle(40, 25, 11, 0);
    display.setCursor(0, 55);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(&Org_01);
    display.setTextWrap(0);
    display.setCursor(15, 55);
    display.printf("%s @ H-BRS", AUTHOR);
    display.display();
    Serial.println("Done!");
    delay(5000);
    display.clearDisplay();
    display.setCursor(0, 5);
}

void updateDisplay(float temp, float hum, bool windowOpen, bool fanOn) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(&Org_01);
    display.setCursor(0, 5);
    display.printf("%s@H-BRS", AUTHOR);
    display.setCursor(0, 28);
    display.println("Sensor AHT_10:");
    display.setCursor(0, 38);
    display.println("Temp:");
    display.setCursor(0, 46);
    display.println("Hum:");
    display.setCursor(0, 54);
    display.println("Window:");
    display.setCursor(0, 62);
    display.println("Fan:");
    display.setCursor(37, 38);
    display.printf("%.2f C", temp);
    display.setCursor(37, 46);
    display.printf("%.2f %%rH", hum);
    display.setCursor(37, 54);
    display.printf("%s", windowOpen ? "Open" : "Closed");
    display.setCursor(37, 62);
    display.printf("%s", fanOn ? "On" : "Off");
    
    // Logo
    display.fillCircle(113, 20, 10, 1);
    display.fillCircle(85, 20, 10, 1);
    display.fillCircle(85, 20, 6, 0);
    display.display();
}

void displayMessage(String message) {
    Serial.print(message);
    display.print(message);
    display.display();
}