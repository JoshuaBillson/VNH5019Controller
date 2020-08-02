# VNH5019Controller Arduino Library

## Summary
This library provides the VNH5019_Controller class to generate valid messages and communicate with the
motor controller via either I2C or USB from an Arduino compatible device.

## Classes
**VNH5019_Controller**

## VNH5019_Controller Methods
**mount(mode)**\
Open I2C and Serial Ports For Writing To The Controller; Called In setup()\
mode: The Method Of Communication, Either I2C or SRL

**writeSpeed(channel, value)**\
Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels\
channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write From -100 to 100

**writeBrake(channel, value)**\
Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels\
channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write From 0 to 100

**writeMixedCommand(speedVal, turnVal)**\
Write A Mixed Command\
speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward)\
turnVal: A Value From -100 (Full Left) To 100 (Full Right)

**stop()**\
Stop Both Motors By Applying Maximum Braking

**setActive()**\
Put the controller into an active state.

**setStandby()**\
Put the controller into a standby state.
