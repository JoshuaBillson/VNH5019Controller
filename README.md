# Open Source VNH5019 Motor Controller

## Summary
The purpose of this project is to create an I2C and USB enabled motor controller powered by a [Dual VNH5019 Motor Driver
Shield](https://www.pololu.com/product/2507) coupled with an Arduino Uno. The project aims to provide firmware for the Arduino
Uno as well as C++ and Python libraries for interfacing from an external device.

## Features
The motor controller can be switched between two primary states: standby and active. In standby, the controller will not
write any commands to the connected motors. As a safety feature, the controller powers up into standby mode and must be 
instructed to switch to an active state before it will respond to any motor-related directives. In addition, an LED and 
piezo buzzer may be connected to pins 5 and 13 respectively to provide audio-visual confirmation regarding its state. The
Arduino receiver will listen over both I2C and USB Serial for commands and will respond to either without placing any 
expectations on the transmitting device.

## Firmware
The software for the Arduino Uno controller is included in the Firmware directory. It requires the user to install the
[DualVNH5019MotorShield library](https://github.com/pololu/dual-vnh5019-motor-shield) in their Arduino/libraries folder
in order to run. Once this pre-requisite is met, put the Firmware folder into your sketches directory and upload it as usual.

## Arduino Library
The Arduino library for interfacing with the controller from an external Arduino is provided in the Arduino folder. Simply 
save the Arduino/VNH5019Controller folder to your Arduino/libraries directory and include it in your sketches with **#include 
VNH5019Controller.h**. Refer to the Arduino README and the provided example sketch for more info.

## Python Library
A [Python library](https://pypi.org/project/VNH5019-Serial-Controller/) for interfacing with the controller from an external 
device has been provided and is hosted on the Python Package Index. Simply **pip install VNH5019-Serial-Controller** to make
use of it. Documentation as well as an example sketch has been provided in the Python folder.

## Audio-Visual Feedback And Wiring
LED and Audio feedback denoting the state of the controller is included in the firmware. When
the controller first powers up, a start-up chime will play and an LED will light up. Whilst the controller
is in standby, the LED will blink at regular 2 second intervals but will change to a solid light when the controller
is in an active state. Additionally, a unique chime will play when the controller enters a standby state and when
it enters an active state. Use of this feature is optional, but be aware that the led is controlled
by digital pin 5 and the piezo buzzer is controlled by digital pin 13. Refer to **VNH5019_Controller_Schematic.pdf**
for further wiring details.

## Classes

**VNH5019_Controller**


## VNH5019_Controller Methods

**mount()**\
Open I2C and Serial Ports For Writing To The Controller; Called In setup()

Takes No Arguments And Returns Nothing


**writeSpeed(mode, channel, value)**\
Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels

mode: The Method Of Communication, Either I2C or SRL\
channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write From -100 to 100

Returns: Nothing


**writeBrake(mode, channel, value)**\
Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels

mode: The Method Of Communication, Either I2C or SRL\
channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)\
value: The Value We Want To Write From 0 to 100

Returns: Nothing


**writeMixedCommand(mode, speedVal, turnVal)**\
Write A Mixed Command

mode: The Method Of Communication, Either I2C or SRL\
speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward)\
turnVal: A Value From -100 (Full Left) To 100 (Full Right)

Returns: Nothing


**stop(mode)**\
Stop Both Motors By Applying Maximum Braking

mode: The Method Of Communication, Either I2C or SRL

Returns: Nothing


**setActive(mode)**\
Place The Controller Into An Active State

mode: The Method Of Communication, Either I2C or SRL

Returns: Nothing


**setStandby(mode)**\
Place The Controller Into Standby

mode: The Method Of Communication, Either I2C or SRL

Returns: Nothing
