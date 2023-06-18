#include "battery.h"

int pin = A0; // Analog pin to read raw battery voltage

const float maxVoltage = 2.1; // Maximum Output Voltage
const float minVoltage = 1.375; // Cutoff Voltage
const float calibration = 0.25; // Calibration of dropout voltage for adjustment

float getBatteryPercentage() {
    float voltage = (float) analogRead(pin) * 3.3 / 1023 + calibration;
    if (voltage <= minVoltage) {
        return 0;
    }
    return (voltage - minVoltage) / (maxVoltage - minVoltage) * 100;
}