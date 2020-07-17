#include "VNH5019Controller.h"

VNH5019_Controller controller;

void setup() {
  // put your setup code here, to run once:
  controller.mount(I2C);
  delay(2000);
}

void loop() {
  /* Enter Active */
  controller.setActive();
  delay(2000);

  /* Accelerate Forward */
  for (int8_t i = 0; i <= 100; i++) {
    controller.writeSpeed(BOTH, i);
    delay(10);
  }
  delay(1000);
  controller.stop();
  delay(1000);

   /* Accelerate Backward */
  for (int8_t i = 0; i >= -100; i--) {
    controller.writeSpeed(BOTH, i);
    delay(10);
  }
  delay(1000);
  controller.stop();
  delay(1000);

  /* Turn Left Forward */
  controller.writeMixedCommand(100, -50);
  delay(1000);
  controller.stop();
  delay(1000);

  /* Turn Right Forward */
  controller.writeMixedCommand(100, 50);
  delay(1000);
  controller.stop();
  delay(1000);

  /* Turn Left Backward */
  controller.writeMixedCommand(-100, -50);
  delay(1000);
  controller.stop();
  delay(1000);

  /* Turn Right Backward */
  controller.writeMixedCommand(-100, 50);
  delay(1000);
  controller.stop();
  delay(1000);

  /* Enter Standby */
  controller.setStandby();
  delay(5000);
}
