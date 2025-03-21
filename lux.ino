#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int LDR_PIN = A0;
const int LED_PIN = 9;  // TCS3472 LED control (PWM)
const float R_FIXED = 2200.0; // Use 1000.0 if using 1kΩ resistor
const float VCC = 5.0;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_16X);

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    analogWrite(LED_PIN, 255); // Start at max brightness

    if (!tcs.begin()) {
        Serial.println("No TCS3472 sensor found!");
        while (1);
    }

    Serial.println("Lux, Vout (V), R_LDR (Ω)");
}

void loop() {
    for (int brightness = 255; brightness >= 0; brightness -= 25) {  // Step brightness down
        analogWrite(LED_PIN, brightness);
        delay(1000);  // Allow LDR to adjust

        // Read light intensity
        uint16_t clear, red, green, blue;
        tcs.getRawData(&red, &green, &blue, &clear);
        float lux = clear;  // Approximates lux

        // Read LDR voltage
        int rawValue = analogRead(LDR_PIN);
        float Vout = (rawValue / 1023.0) * VCC;
        float R_LDR = R_FIXED * ((VCC / Vout) - 1);

        // Print results
        Serial.print(lux);
        Serial.print(", ");
        Serial.print(Vout);
        Serial.print(", ");
        Serial.println(R_LDR);

        delay(2000);  // Wait before next brightness level
    }

    Serial.println("Cycle complete. Restarting...");
    delay(5000);  // Restart cycle after a pause
}
