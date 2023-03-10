#pragma once

#include <Arduino.h>

#define NTC_PIN A0                 // Pin, to which the voltage divider is connected
#define NOMINAL_RESISTANCE 100000  // Nominal resistance at 25⁰C
#define NOMINAL_TEMPERATURE 25     // temperature for nominal resistance (almost always 25⁰ C)
#define SAMPLING_RATE 5            // Number of samples
#define THERMISTOR_BETA 3950       // The beta coefficient or the B value of the thermistor (usually 3000-4000) check the datasheet for the accurate value.
#define VD_RESISTANCE 100000       // Value of  resistor used for the voltage divider

class HotplateTemperatureSensor {
   private:
    int samples = 0;

   public:
    float getTemperature();
};