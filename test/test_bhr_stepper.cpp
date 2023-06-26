#include "unity.h"
#include "BHRStepper.h"

void setUp(void) {
  // Serial.begin(9600);
}

void tearDown(void) {
  // clean stuff up here
}

void test_on_off_switch(void) {
    BHRStepper motor = BHRStepper(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
    motor.setHalfStep(false);
    motor.setOn(false);
    motor.setDirection(true);
    // set delay to 1ms
    motor.setSpeed(1);
    TEST_ASSERT_EQUAL(LOW, motor.readPin1());
    TEST_ASSERT_EQUAL(LOW, motor.readPin2());
    TEST_ASSERT_EQUAL(LOW, motor.readPin3());
    TEST_ASSERT_EQUAL(LOW, motor.readPin4());
    TEST_ASSERT_EQUAL(0, motor.getCurrentStep());
    TEST_ASSERT_EQUAL(0, motor.getLastStepTime());
    // first step
    motor.forceNextStep();
    motor.loop();
    // all pins should still be low
    TEST_ASSERT_EQUAL(LOW, motor.readPin1());
    TEST_ASSERT_EQUAL(LOW, motor.readPin2());
    TEST_ASSERT_EQUAL(LOW, motor.readPin3());
    TEST_ASSERT_EQUAL(LOW, motor.readPin4());
    TEST_ASSERT_EQUAL(0, motor.getCurrentStep());
    motor.setOn(true);
    motor.forceNextStep();
    // second step
    motor.loop();
    TEST_ASSERT_EQUAL(1, motor.getCurrentStep());
    TEST_ASSERT_EQUAL(LOW, motor.readPin1());
    TEST_ASSERT_EQUAL(HIGH, motor.readPin2());
    TEST_ASSERT_EQUAL(LOW, motor.readPin3());
    TEST_ASSERT_EQUAL(LOW, motor.readPin4());
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_on_off_switch);
  return UNITY_END();
}

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
  return runUnityTests();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}