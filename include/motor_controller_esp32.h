#pragma once

#include <Arduino.h>

class MotorController {
    const uint8_t STEP = 2;
    const uint16_t MAX_DUTY = 200;
    const uint8_t MIN_DUTY = 3;
    const uint8_t ledChannel = 0;
    const uint32_t freq = FREQUENCY;
    const uint8_t resolution = 8;
    const uint8_t ledPin = PIN_MOTOR_OUTPUT;

    public:

    void initialize() {
        ledcSetup(ledChannel, freq, resolution);
        ledcAttachPin(ledPin, ledChannel);
        turnOff();
        flush();
    }
    
    uint8_t speedUp() {
        uint8_t step = increase();
        flush();
        return step;
    }

    uint8_t slowDown() {
        uint8_t step = decrease();
        flush();
        return step;
    }

    private:

    uint16_t currentState = 0;

    void turnOff() {
        digitalWrite(PIN_MOTOR_OUTPUT, LOW);
        currentState = 0;
    }

    uint8_t increase() {
        if ((currentState + STEP) > MAX_DUTY) {
            return 0;
        }
        currentState += STEP;
        return STEP;
    }

    uint8_t decrease() {
        if ((currentState - STEP) < MIN_DUTY) {
            return 0;
        }
        currentState -= STEP;
        return STEP;
    }

    void set(int newSetting) {
        currentState = newSetting;
    }

    uint8_t setSpeed(uint8_t newSpeed)
    {
        uint8_t step = 0;
        if (currentState < newSpeed) {
            while (currentState < newSpeed)
            {
                step += speedUp();
            }
            return step;
        }
        if (currentState > newSpeed) {
            while (currentState > newSpeed) {
                step+= slowDown();
            }
            return step;
        }
        return 0;
    }

    void flush() {
        ledcWrite(ledChannel, currentState);
    }
};