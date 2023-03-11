#pragma once

#include <Arduino.h>

#define BUZZER PIN6

// BUZZER TONE FREQUENCIES
#define TONE_3000 3000
#define TONE_3500 3500
#define TONE_4000 4000
#define TONE_5000 5000

class HotplateBuzzer {
    struct TonePattern {
        unsigned int frequency;
        unsigned long duration;
    };

   private:
    void playTone(TonePattern pattern[], uint8_t size);

   public:
    void init();
    void startupTone();
    void menuTone();
    void valueChangeTone();
    void confirmSelectionTone();
    void programStartTone();
    void programFinishTone();
    void resetTone();
};