#pragma once

#include <Arduino.h>

#define SSR_PIN 10

class HotplateSSR {
    public:
     void init();
     void setPWM(uint8_t pwm);
};