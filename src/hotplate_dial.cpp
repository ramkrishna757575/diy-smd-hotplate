#include "hotplate_dial.h"

HotplateDial* HotplateDial::sHotplateDial = 0;

void HotplateDial::init() {
    sHotplateDial = this;

    // Set encoder pins as inputs
    pinMode(DIAL_CLK, INPUT);
    pinMode(DIAL_DT, INPUT);

    // Read the initial state of CLK
    lastStateCLK = digitalRead(DIAL_CLK);

    // Call hotplateDialISR() when any high/low changed seen
    // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
    attachInterrupt(digitalPinToInterrupt(DIAL_CLK), HotplateDial::hotplateDialISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DIAL_DT), HotplateDial::hotplateDialISR, CHANGE);
}

void HotplateDial::updateCount() {
    // Read the current state of CLK
    currentStateCLK = digitalRead(DIAL_CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK && currentStateCLK == HIGH) {
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DIAL_DT) != currentStateCLK) {
            counter--;
        } else {
            // Encoder is rotating CW so increment
            counter++;
        }
    }

    // Remember last CLK state
    lastStateCLK = currentStateCLK;
}

uint8_t HotplateDial::getCount() {
    return counter;
}

void HotplateDial::setCount(uint8_t count) {
    counter = count;
}

void HotplateDial::hotplateDialISR() {
    if (sHotplateDial != 0)
        sHotplateDial->updateCount();
}
