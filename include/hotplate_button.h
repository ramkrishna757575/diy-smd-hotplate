#pragma once

#include <Arduino.h>

#define BUTTON_1_PIN 7
#define BUTTON_2_PIN 8
#define BUTTON_3_PIN 9

#define DEBOUNCE_DELAY 100

class HotplateButton {
    private:
     uint8_t mButtonPin;
     bool mIsPressed = false;
     unsigned long mStartTime = 0;

    public:
     void setButtonPin(uint8_t pin);
     bool isPressed();
};