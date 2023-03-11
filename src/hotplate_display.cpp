#include "hotplate_display.h"

HotplateDisplay::HotplateDisplay() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &WIRE);
}

void HotplateDisplay::init() {
    // initialize the OLED object
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
    }
}

void HotplateDisplay::setCursor(uint16_t x, uint16_t y) {
    display.setCursor(x, y);
}

void HotplateDisplay::print(String str, uint8_t size, bool clear) {
    if (clear) {
        display.clearDisplay();
    }
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.print(str);
}

void HotplateDisplay::println(String str, uint8_t size, bool clear) {
    if (clear) {
        display.clearDisplay();
    }
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.println(str);
}

void HotplateDisplay::updateDisplay() {
    display.display();
}

void HotplateDisplay::clearDisplay() {
    display.setCursor(0, 0);
    display.print("");
}
