#include "VNH5019Controller.h"
#include <Servo.h>

#define servoPin 5

VNH5019_Controller controller;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  controller.mount();
  servo.attach(servoPin);
  servo.write(90);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  controller.setActive(I2C);
  delay(2000);

  for (int8_t i = 0; i <= 100; i++) {
    controller.writeSpeed(I2C, BOTH, i);
    delay(10);
  }
  delay(1000);

  controller.stop(I2C);
  delay(1000);

  for (int8_t i = 0; i >= -100; i--) {
    controller.writeSpeed(I2C, BOTH, i);
    delay(10);
  }
  delay(1000);

  controller.stop(I2C);
  delay(1000);


  controller.setStandby(I2C);
  delay(5000);
}
