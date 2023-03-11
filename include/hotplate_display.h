#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define WIRE Wire

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C

class HotplateDisplay {
   private:
    Adafruit_SSD1306 display;

   public:
    HotplateDisplay();
    void init();
    void setCursor(uint16_t x, uint16_t y);
    void print(String, uint8_t size = 1, bool clear = false);
    void println(String, uint8_t size = 1, bool clear = false);
    void updateDisplay();
    void clearDisplay();
};