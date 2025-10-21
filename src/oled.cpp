#include "oled.h"
#include "SerialAliases.h"

bool OLED::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial_1.println(F("SSD1306 allocation failed"));
        return false;
    } else {
        display.clearDisplay();
        return true;
    }
}

void OLED::updateDisplay() {
    this->clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    
    this->showDisplay();
}

void OLED::clearDisplay() {
    display.clearDisplay();
}

void OLED::showDisplay() {
    display.display();
}
