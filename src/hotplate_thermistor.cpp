#include "hotplate_thermistor.h"

float HotplateThermistor::getTemperature() {
    uint8_t i;
    float average;
    samples = 0;

    // activate sensor voltage
    for (i = 0; i < SAMPLING_RATE; i++) {
        samples += analogRead(NTC_PIN);
        delay(10);
    }
    average = 0;
    average = samples / SAMPLING_RATE;

    // Calculate NTC resistance
    average = 1023 / average - 1;
    average = VD_RESISTANCE / average;
    float temperature;
    temperature = average / NOMINAL_RESISTANCE;           // (R/Ro)
    temperature = log(temperature);                       // ln(R/Ro)
    temperature /= THERMISTOR_BETA;                       // 1/B * ln(R/Ro)
    temperature += 1.0 / (NOMINAL_TEMPERATURE + 273.15);  // + (1/To)
    temperature = 1.0 / temperature;                      // Invert
    temperature -= 273.15;
    return temperature;
}
