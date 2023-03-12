#include "hotplate_pid_controller.h"

HotplatePIDController* HotplatePIDController::sHotplatePIDController = 0;

void HotplatePIDController::init() {
    sHotplatePIDController = this;
    temp.set(PID_REFRESH_RATE, HotplatePIDController::PIDCallback);
}

void HotplatePIDController::runPIDLoop() {
    if (millis() - previousMillis >= 1000) {
        previousMillis = millis();
        tempRead = thermocouple.readCelsius();
    }

    if (reflowProcess) {
        if (!startTimer) {
            setPoint = ambTemp;
            startTime = previousTime = millis();
            startTimer = true;
            Serial.println("SetPoint PID TempRead");
        }

        currentTime = millis();
        elapsedTime = (currentTime - previousTime) / 300;

        int t1 = profile[ID].heatup_time * 1000;
        int t2 = t1 + (profile[ID].soak_time * 1000);
        int t3 = t2 + (profile[ID].rampup_time * 1000);
        int t4 = t3 + (profile[ID].peak_time * 1000);

        if (currentTime - startTime < t1) {
            setPoint += (float(profile[ID].soak - 0) / profile[ID].heatup_time);
            if (setPoint > profile[ID].soak) setPoint = profile[ID].soak;
        }
        if (currentTime - startTime > t1 && currentTime - startTime < t2) {
            setPoint += (float(profile[ID].reflow - profile[ID].soak) / profile[ID].soak_time);
            if (setPoint > profile[ID].reflow) setPoint = profile[ID].reflow;
        }
        if (currentTime - startTime > t2 && currentTime - startTime < t3) {
            setPoint += (float(profile[ID].peak - profile[ID].reflow) / profile[ID].rampup_time);
            if (setPoint > profile[ID].peak) setPoint = profile[ID].peak;
        }
        if (currentTime - startTime > t3 && currentTime - startTime < t4) {
            setPoint = profile[ID].peak;
        }
        if (currentTime - startTime > t4) {
            setPoint = ambTemp;
            digitalWrite(fan, LOW);

            if (tempRead < ambTemp + 10) {
                reflowProcess = false;
                digitalWrite(fan, HIGH);
                iTerm = 0;
                plotter = 0;
                lastError = 0;
                startTimer = false;
                start = false;
                home = true;
                delay(500);
                tft.fillScreen(TFT_BLACK);
            }
        }

        error = setPoint - tempRead;

        // Proportional
        pTerm = error;

        // Integral
        if (error > -3 && error < 3)
            iTerm += error;

        // Anti-wind-up
        iTerm = constrain(iTerm, 0, 100);

        // Derivative
        dTerm = (error - lastError) / elapsedTime;

        // Calculate PID
        PID_value = kP * pTerm + kI * iTerm + kD * dTerm;

        // Deadband
        PID_value = constrain(PID_value, 0, 255);

        analogWrite(heater, PID_value);

        Serial.print(setPoint);
        Serial.print(",");
        Serial.print(PID_value);
        Serial.print(",");
        Serial.println(tempRead);

        lastError = error;
        previousTime = currentTime;
    }
}

void HotplatePIDController::PIDCallback() {
    if (sHotplatePIDController != 0)
        sHotplatePIDController->runPIDLoop();
}