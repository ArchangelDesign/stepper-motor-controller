
#pragma once
#include <Arduino.h>

typedef const uint8_t bhr_step_t[4];

class BHRStepper {

    public:

    BHRStepper(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
    {
        this->pin1 = pin1;
        this->pin2 = pin2;
        this->pin3 = pin3;
        this->pin4 = pin4;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
    }

    void loop()
    {
        step();
    }

    void setSpeed(uint8_t delay)
    {
        millisDelay = delay;
        if (millisDelay < 2) {
            millisDelay = 1;
        }
    }

    void setHalfStep(bool halfStep)
    {
        this->halfStep = halfStep;
    }

    void setOn(bool on)
    {
        this->on = on;
    }

    bool isOn()
    {
        return on;
    }

    bool isHalfStep()
    {
        return halfStep;
    }

    bool isRight()
    {
        return right;
    }

    void setDirection(bool right)
    {
        this->right = right;
    }

    uint8_t readPin1()
    {
        return pin1State;
    }

    uint8_t readPin2()
    {
        return pin2State;
    }

    uint8_t readPin3()
    {
        return pin3State;
    }

    uint8_t readPin4()
    {
        return pin4State;
    }

    void forceNextStep()
    {
        force = true;
    }

    uint8_t getCurrentStep()
    {
        return currentStep;
    }

    uint16_t getLastStepTime()
    {
        return lastStepTime;
    }

    private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pin3;
    uint8_t pin4;
    int8_t currentStep = 0;
    bool halfStep = true;
    uint16_t millisDelay = 1000;
    uint32_t lastStepTime = 0;
    bool on = false;
    bool right = true;
    bool force = false;
    uint8_t pin1State = LOW;
    uint8_t pin2State = LOW;
    uint8_t pin3State = LOW;
    uint8_t pin4State = LOW;

    bhr_step_t fullStepMap[4] = {
        {HIGH, LOW, LOW, LOW},
        {LOW, HIGH, LOW, LOW},
        {LOW, LOW, HIGH, LOW},
        {LOW, LOW, LOW, HIGH}
    };


    bhr_step_t halfStepMap[8] = {
        {HIGH, LOW, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {LOW, HIGH, LOW, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, LOW, HIGH, LOW},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, LOW, HIGH},
        {HIGH, LOW, LOW, HIGH},
    };

    uint8_t getMaxSteps()
    {
        if (isHalfStep()) {
            return 8;
        }
        return 4;
    }

    void flushStep()
    {
        if (!isOn()) {
            return;
        }
        if (isHalfStep()) {
            digitalWrite(pin1, halfStepMap[currentStep][0]);
            digitalWrite(pin2, halfStepMap[currentStep][1]);
            digitalWrite(pin3, halfStepMap[currentStep][2]);
            digitalWrite(pin4, halfStepMap[currentStep][3]);
            pin1State = halfStepMap[currentStep][0];
            pin2State = halfStepMap[currentStep][1];
            pin3State = halfStepMap[currentStep][2];
            pin4State = halfStepMap[currentStep][3];
            lastStepTime = millis();
            return;
        }
        digitalWrite(pin1, fullStepMap[currentStep][0]);
        digitalWrite(pin2, fullStepMap[currentStep][1]);
        digitalWrite(pin3, fullStepMap[currentStep][2]); 
        digitalWrite(pin4, fullStepMap[currentStep][3]);
        pin1State = fullStepMap[currentStep][0];
        pin2State = fullStepMap[currentStep][1];
        pin3State = fullStepMap[currentStep][2];
        pin4State = fullStepMap[currentStep][3];
        lastStepTime = millis();
    }

    void step() {
        if ((lastStepTime + millisDelay) > millis() && !force) {
            return;
        }
        if (!isOn()) {
            return;
        }
        force = false;
        currentStep += isRight() ? 1 : -1;
        if (currentStep > getMaxSteps() - 1 && isRight()) {
            currentStep = 0;
        }
        if (currentStep < 0 && !isRight()) {
            currentStep = getMaxSteps() - 1;
        }
        flushStep();
    }
};