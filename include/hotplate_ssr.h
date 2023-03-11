#pragma once

#include <Arduino.h>

#define SSR_PIN 10

class HotplateSSR {
    private:
     bool mIsHeaterActive = false;

    public:
     void init();
     void setPWM(uint8_t pwm);
     bool isHeaterActive();
};