# VNH5019 Controller

## Abstract

The purpose of this library is to provide a means of controlling a [Dual VNH5019 Motor Driver
Shield](https://www.pololu.com/product/2507) coupled with an Arduino Uno.

## Classes

**VNH5019_Controller**

## Functions

**VNH5019_Controller::mount()**\
Open I2C and Serial Ports For Writing To The Controller; Called In setup()\
Takes No Arguments And Returns Nothing\


**VNH5019_Controller::writeSpeed(mode, channel, value)**\
Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels\
writeMode: The Method Of Communication, Either I2C or SRL\
channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write\


**VNH5019_Controller::writeBrake(mode, channel, value)**\
Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels\
writeMode: The Method Of Communication, Either I2C or SRL\
channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write\


**VNH5019_Controller::writeMixedCommand(mode, speedVal, turnVal)**\
Write A Mixed Command\
writeMode: The Method Of Communication, Either I2C or SRL\
speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward)\
turnVal: A Value From -100 (Full Left) To 100 (Full Right)\


**VNH5019_Controller::stop(mode)**\
Stop Both Motors By Applying Maximum Braking\
writeMode: The Method Of Communication, Either I2C or SRL\


**VNH5019_Controller::setActive(mode)**\
Place The Controller Into An Active State\
writeMode: The Method Of Communication, Either I2C or SRL\


**VNH5019_Controller::setStandby(mode)**\
Place The Controller Into Standby\
writeMode: The Method Of Communication, Either I2C or SRL\
