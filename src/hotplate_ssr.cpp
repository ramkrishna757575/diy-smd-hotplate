#include "hotplate_ssr.h"

void HotplateSSR::init() {
    pinMode(SSR_PIN, OUTPUT);
}

void HotplateSSR::setPWM(uint8_t pwm) {
    mIsHeaterActive = pwm > 0;
    analogWrite(SSR_PIN, pwm);
}

bool HotplateSSR::isHeaterActive() {
    return mIsHeaterActive;
}