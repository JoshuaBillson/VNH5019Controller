# VNH5019Controller Arduino Library
This library provides the VNH5019_Controller class to generate valid messages and communicate with the
motor controller via either I2C or USB from an Arduino compatible device.

# Classes
### VNH5019_Controller

# VNH5019_Controller Methods
### mount( mode )
Open I2C and Serial Ports For Writing To The Controller; Called In setup()\
##### mode

Type: `Byte`  

The Method Of Communication, Either I2C or SRL  

### writeSpeed( channel, value )
Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels  
##### channel: 

Type: `Byte`  

The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)  

##### value 

Type: `int8_t`  

The Value We Want To Write From -100 to 100  

### writeBrake( channel, value )
Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels\
##### channel: 

Type: `Byte`  

The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)  

##### value 

Type: `int8_t`  

The Value We Want To Write From 0 to 100  

### writeMixedCommand( speedVal, turnVal )
Write A Mixed Command  
##### speedVal: 

Type: `int8_t`  

A Value From -100 (Full Reverse) To 100 (Full Forward)  

##### turnVal 

Type: `int8_t`  

A Value From -100 (Full Left) To 100 (Full Right)  

### stop()  
Stop Both Motors By Applying Maximum Braking

### setActive()  
Put the controller into an active state.  

setStandby()  
Put the controller into a standby state.  

# Example
```cpp
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
```
