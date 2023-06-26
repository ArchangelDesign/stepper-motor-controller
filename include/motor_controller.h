#pragma once

#include <Arduino.h>
#include <Stepper.h>
#include <BHRStepper.h>

class MotorController {
    const uint8_t STEP = 2;
    const uint16_t MAX_DUTY = 220;
    const uint8_t MIN_DUTY = 3;

    public:

    void initialize() {
        pinMode(PIN_MOTOR_OUTPUT, OUTPUT);
        pinMode(PIN_POTENTIOMETER, INPUT);
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

    uint8_t setSpeed(uint8_t newSpeed)
    {
        motor.setSpeed(newSpeed);
    }

    void loop() {
        motor.loop();
    }

    private:

    uint16_t currentState = 0;
    // Stepper motor = Stepper(STEPS_PER_REVOLUTION, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
    BHRStepper motor = BHRStepper(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

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

    void flush() {
        analogWrite(PIN_MOTOR_OUTPUT, currentState);
    }
};