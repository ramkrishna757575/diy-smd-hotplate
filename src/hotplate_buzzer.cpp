#include "hotplate_buzzer.h"

void HotplateBuzzer::init() {
    pinMode(BUZZER, OUTPUT);
}

void HotplateBuzzer::playTone(TonePattern pattern[], uint8_t size) {
    for (int i = 0; i < size; i++) {
        tone(BUZZER, pattern[i].frequency, pattern[i].duration);
        delay(pattern[i].duration);
    }
}

void HotplateBuzzer::startupTone() {
    TonePattern pattern[3] = {{TONE_4000, 100}, {TONE_3000, 100}, {TONE_4000, 100}};
    playTone(pattern, 3);
}

void HotplateBuzzer::menuTone() {
    TonePattern pattern[1] = {{TONE_4000, 100}};
    playTone(pattern, 1);
}

void HotplateBuzzer::valueChangeTone() {
    TonePattern pattern[1] = {{TONE_5000, 50}};
    playTone(pattern, 1);
}

void HotplateBuzzer::confirmSelectionTone() {
    TonePattern pattern[1] = {{TONE_3500, 200}};
    playTone(pattern, 1);
}

void HotplateBuzzer::programStartTone() {
    TonePattern pattern[1] = {{TONE_3000, 1000}};
    playTone(pattern, 1);
}

void HotplateBuzzer::programFinishTone() {
    TonePattern pattern[2] = {{TONE_3500, 200}, {TONE_3000, 200}};
    playTone(pattern, 2);
}

void HotplateBuzzer::resetTone() {
    TonePattern pattern[5] = {{TONE_3000, 50}, {0, 50}, {TONE_3000, 50}, {0, 50}, {TONE_3000, 50}};
    playTone(pattern, 5);
}
