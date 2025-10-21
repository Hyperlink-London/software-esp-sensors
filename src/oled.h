#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
private:
    static const int SCREEN_WIDTH = 128; // OLED display width, in pixels
    static const int SCREEN_HEIGHT = 64; // OLED display height, in pixels
    static const int SCREEN_ADDRESS = 0x3C; // OLED I2C address
    
    Adafruit_SSD1306 display;

public:
    OLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}
    bool begin();
    
    // Update display with sensor data
    void updateDisplay();
    void clearDisplay();
    void showDisplay();
};

#endif
