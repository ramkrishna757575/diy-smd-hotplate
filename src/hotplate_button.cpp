#include "hotplate_button.h"

void HotplateButton::setButtonPin(uint8_t pin) {
    mButtonPin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool HotplateButton::isPressed() {
    unsigned long elapsed_time = millis() - mStartTime;
    if (elapsed_time > DEBOUNCE_DELAY && !mIsPressed && digitalRead(mButtonPin) == LOW) {
        mIsPressed = true;
        mStartTime = millis();
    } else if (elapsed_time > DEBOUNCE_DELAY && mIsPressed && digitalRead(mButtonPin) == HIGH) {
        mIsPressed = false;
    }
    return mIsPressed;
}
