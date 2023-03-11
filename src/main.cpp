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

bool isProgramModeSelected = false, isProgramOptionConfirmed = false, isProgramRunning = false;
bool isReflowCurveMode = true, profile138 = true;

uint8_t targetTemp = MIN_TEMPERATURE;

void setup() {
    Serial.begin(9600);
    // Initialize display and show welcome text
    hotplateDisplay.init();
    hotplateDisplay.setCursor(0, 0);
    hotplateDisplay.println("Welcome", 2, true);
    hotplateDisplay.println("DIY SMD Hotplate", 1);
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
    if (!isProgramRunning) {
        if (!isProgramModeSelected) {
            hotplateDisplay.setCursor(0, 0);
            hotplateDisplay.println("Select Program Mode:", 1, true);
            if (isReflowCurveMode) {
                hotplateDisplay.println(">> Reflow Curve", 1);
            } else {
                hotplateDisplay.println(">> Fixed Temperature", 1);
            }
            if (button1.isPressed()) {
                isReflowCurveMode = !isReflowCurveMode;
                hotplateBuzzer.menuTone();
            }
            if (button2.isPressed()) {
                isProgramModeSelected = true;
                hotplateBuzzer.confirmSelectionTone();
            }
        } else if (!isProgramOptionConfirmed) {
            hotplateDisplay.setCursor(0, 0);
            if (isReflowCurveMode) {
                hotplateDisplay.println("Reflow Curve Mode", 1, true);
                hotplateDisplay.println("Select Profile:");
                if (profile138) {
                    hotplateDisplay.println(">> Profile 138", 1);
                } else {
                    hotplateDisplay.println(">> Profile 183", 1);
                }
                if (button1.isPressed()) {
                    profile138 = !profile138;
                    hotplateBuzzer.menuTone();
                }
                if (button2.isPressed()) {
                    isProgramOptionConfirmed = true;
                    hotplateBuzzer.confirmSelectionTone();
                }
            } else {
                hotplateDisplay.println("Fixed Temp Mode", 1, true);
                hotplateDisplay.println(">> Set Temp: " + String(hotplateDial.getCount()), 1);
                if (button2.isPressed()) {
                    targetTemp = hotplateDial.getCount();
                    isProgramOptionConfirmed = true;
                    hotplateBuzzer.confirmSelectionTone();
                }
            }
        } else {
            hotplateDisplay.setCursor(0, 0);
            if (isReflowCurveMode) {
                hotplateDisplay.println("Reflow Curve", 1, true);
                if (profile138) {
                    hotplateDisplay.println(String("138 ") + (char)247 + " Profile", 1);
                } else {
                    hotplateDisplay.println(String("183 ") + (char)247 + " Profile", 1);
                }
            } else {
                hotplateDisplay.println("Fixed Temperature", 1, true);
                hotplateDisplay.println("Temp Set Point: " + String(targetTemp) + (char)247 + "C", 1);
            }
            hotplateDisplay.println("START ?", 1);
            if (button2.isPressed()) {
                isProgramRunning = true;
                hotplateBuzzer.programStartTone();
            } else if (button3.isPressed()) {
                isProgramModeSelected = false;
                isProgramOptionConfirmed = false;
                isProgramRunning = false;
                isReflowCurveMode = true;
                profile138 = true;
                hotplateBuzzer.resetTone();
            }
        }
    } else {
        isProgramRunning = true;
        hotplateDisplay.setCursor(0, 0);
        hotplateDisplay.println("Kp: Ki: Kd:", true);
        hotplateDisplay.println("Tc: " + String(hotplateThermistor.getTemperature()) + " " + (char)247 + "C", 1, true);
        hotplateDisplay.println("Tt: " + String(targetTemp) + " " + (char)247 + "C", 1);
        if(button3.isPressed()) {
            isProgramModeSelected = false;
            isProgramOptionConfirmed = false;
            isProgramRunning = false;
            isReflowCurveMode = true;
            profile138 = true;
            hotplateSSR.setPWM(0);
            hotplateBuzzer.resetTone();
        }
    }

    /* float temperature = hotplateThermistor.getTemperature();
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
    hotplateDisplay.println("Dial: " + String(hotplateDial.getCount()), 1, false); */
    hotplateDisplay.updateDisplay();
}