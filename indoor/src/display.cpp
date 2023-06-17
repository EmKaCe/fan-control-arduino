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

void updateDisplay(float temp, float hum) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(&Org_01);
    display.setCursor(0, 5);
    display.printf("%s@H-BRS", AUTHOR);
    display.setCursor(0, 30);
    display.println("Sensor AHT_10:");
    display.setCursor(0, 50);
    display.println("Temp:");
    display.setCursor(0, 57);
    display.println("Hum:");
    display.setCursor(37, 50);
    display.printf(" %.2f C", temp);
    display.setCursor(37, 57);
    display.printf("%.2f %%rH", hum);
    
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