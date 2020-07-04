# VNH5019 Controller

## Abstract

The purpose of this library is to provide a means of controlling a [Dual VNH5019 Motor Driver
Shield](https://www.pololu.com/product/2507) coupled with an Arduino Uno.

## Classes

**VNH5019_Controller**

## Functions

**VNH5019_Controller::mount()** \n
Open I2C and Serial Ports For Writing To The Controller; Called In setup() \n
Takes No Arguments And Returns Nothing \n


**VNH5019_Controller::writeSpeed(mode, channel, value)** \n
Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels \n
writeMode: The Method Of Communication, Either I2C or SRL \n
channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH) \n
value: The Value We Want To Write \n


**VNH5019_Controller::writeBrake(mode, channel, value)** \n
Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels \n
writeMode: The Method Of Communication, Either I2C or SRL \n
channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH) \n
value: The Value We Want To Write \n


**VNH5019_Controller::writeMixedCommand(mode, speedVal, turnVal)** \n
Write A Mixed Command \n
writeMode: The Method Of Communication, Either I2C or SRL \n
speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward) \n
turnVal: A Value From -100 (Full Left) To 100 (Full Right) \n


**VNH5019_Controller::stop(mode)** \n
Stop Both Motors By Applying Maximum Braking \n
writeMode: The Method Of Communication, Either I2C or SRL \n


**VNH5019_Controller::setActive(mode)** \n
Place The Controller Into An Active State \n
writeMode: The Method Of Communication, Either I2C or SRL \n


**VNH5019_Controller::setStandby(mode)** \n
Place The Controller Into Standby \n
writeMode: The Method Of Communication, Either I2C or SRL \n
