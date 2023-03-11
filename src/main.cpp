#include <Arduino.h>

#include "hotplate_button.h"
#include "hotplate_buzzer.h"
#include "hotplate_dial.h"
#include "hotplate_display.h"
#include "hotplate_ssr.h"
#include "hotplate_thermistor.h"

HotplateDisplay hotplateDisplay;
HotplateThermistor hotplateThermistor;
HotplateBuzzer hotplateBuzzer;
HotplateButton button1, button2, button3;
HotplateSSR hotplateSSR;
HotplateDial hotplateDial;

uint8_t currentCount = 0;

void setup() {
    // Initialize display and show welcome text
    hotplateDisplay.init();
    hotplateDisplay.setCursor(0, 0);
    hotplateDisplay.println("Welcome", 2);
    hotplateDisplay.println("DIY SMD Hotplate", 1, false);
    hotplateDisplay.updateDisplay();

    // Initialize buzzer
    hotplateBuzzer.init();
    hotplateBuzzer.startupTone();

    // Initialize buttons
    button1.setButtonPin(BUTTON_1_PIN);
    button2.setButtonPin(BUTTON_2_PIN);
    button3.setButtonPin(BUTTON_3_PIN);

    // Initialize SSR
    hotplateSSR.init();

    // Initialize Rotary encoder
    hotplateDial.init();

    // small delay before app start
    delay(2000);
}

void loop() {
    float temperature = hotplateThermistor.getTemperature();
    hotplateDisplay.setCursor(0, 0);
    hotplateDisplay.println("Temp: " + String(temperature) + " " + (char)247 + "C");

    if (button1.isPressed()) {
        currentCount++;
        hotplateSSR.setPWM(currentCount);
        hotplateBuzzer.valueChangeTone();
    }
    if (button2.isPressed()) {
        currentCount += 10;
        hotplateSSR.setPWM(currentCount);
        hotplateBuzzer.menuTone();
    }
    if (button3.isPressed()) {
        currentCount = 0;
        hotplateSSR.setPWM(currentCount);
        hotplateBuzzer.confirmSelectionTone();
    }
    hotplateDisplay.println("SSR-PWM: " + String(currentCount), 1, false);
    hotplateDisplay.println("Dial: " + String(hotplateDial.getCount()), 1, false);
    hotplateDisplay.println("Dial: " + String(hotplateDial.getCount()), 1, false);
    hotplateDisplay.updateDisplay();
}