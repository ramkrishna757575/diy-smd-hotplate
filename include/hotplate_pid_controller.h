#pragma once

#include <Arduino.h>
#include <TimerEvent.h>

#define PID_REFRESH_RATE 300

class HotplatePIDController {
   private:
    TimerEvent temp;
    static HotplatePIDController* sHotplatePIDController;
    static void PIDCallback();
    unsigned long previousMillis;
    

   public:
    void init();
    void runPIDLoop();
};