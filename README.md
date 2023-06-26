
# Stepper motor controller for arduino projects
### Works with AVR and ESP platforms

```
#include <Arduino.h>
#include <BHRStepper.h>

BHRStepper motor = BHRStepper(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

void setup() {
  pinMode(PIN_ON, INPUT_PULLUP);
  pinMode(PIN_DIRECTION, INPUT_PULLUP);
  pinMode(PIN_HALF_FULL, INPUT_PULLUP);
}

void loop() {
  uint16_t position = analogRead(1);
  uint8_t newSpeed = map(position, 0, 1023, 0, 255);
  if (newSpeed > 249) {
    newSpeed = 255;
  }
  motor.setSpeed(newSpeed);
  if (digitalRead(PIN_ON) == LOW) {
      motor.setOn(!motor.isOn());
      while(digitalRead(PIN_ON) == LOW) {
          delay(1);
      }
  }
  if (digitalRead(PIN_HALF_FULL) == LOW) {
      motor.setHalfStep(!motor.isHalfStep());
      while (digitalRead(PIN_HALF_FULL) == LOW) {
          delay(1);
      }
  }
  if (digitalRead(PIN_DIRECTION) == LOW) {
      motor.setDirection(!motor.isRight());
      while (digitalRead(PIN_DIRECTION) == LOW) {
          delay(1);
      }
  }
  motor.loop(); 
}
```