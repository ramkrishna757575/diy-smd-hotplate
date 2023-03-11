#pragma once

#include <Arduino.h>

#define DIAL_CLK 2
#define DIAL_DT 3

#define MIN_TEMPERATURE 40
#define MAX_TEMPERATURE 230

class HotplateDial {
   private:
    uint8_t currentStateCLK, lastStateCLK;
    uint8_t counter = MIN_TEMPERATURE;
    static HotplateDial* sHotplateDial;
    static void hotplateDialISR();

   public:
    void updateCount();
    void init();
    uint8_t getCount();
    void setCount(uint8_t count);
};