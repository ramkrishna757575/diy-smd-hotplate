#include "hotplate_ssr.h"

void HotplateSSR::init() {
    pinMode(SSR_PIN, OUTPUT);
}

void HotplateSSR::setPWM(uint8_t pwm) {
    analogWrite(SSR_PIN, pwm);
}
