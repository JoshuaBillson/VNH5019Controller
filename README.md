# VNH5019 Controller

## Overview

The purpose of this library is to provide a means of controlling a [Dual VNH5019 Motor Driver
Shield](https://www.pololu.com/product/2507) coupled with an Arduino Uno over either I2C or serial.
This project uses the standard serial port; to use other hardware serial ports (Serial1, Serial2, etc.)
or Software Serial requires modification to VNH5019Controller.cpp.


## Dependencies

This project makes use of the [DualVNH5019MotorShield library](https://github.com/pololu/dual-vnh5019-motor-shield)
for the firmware running on the Uno Controller and must be installed to you Arduino/libraries
folder.


## Audio-Visual Feedback And Wiring

LED and Audio feedback denoting the state of the controller has been included in the firmware. When
the controller first powers up, a start-up chime will play and an LED will light up. Whilst the controller
is in standby, the LED will blink at regular 2 second intervals and will be solid when the controller
is active. Additionally, a unique chime will play when the controller enters a standby state and when
it enters an active state. Please refer to "VNH5019_Controller_Schematic.pdf" for wiring information.


## Usage

To use this project, download the repository and save it to your Arduino/libraries folder. The firmware
to be uploaded to the Arduino Uno / VNH5019 Motor Driver Shield is contained within Firmware/Firmware.ino.
To interface with the motor controller over either serial or I2C from an external device, use the
VNH5019_Controller class and associated methods.


## Arduino

To interface with the motor controller from an Arduino compatible board, use the Arduino/VNH5019Controller
library. An example sketch has been provided in ArduinoExample/ArduinoExample.ino.


## Raspberry Pi / NVIDIA Jetson

To interface with the motor controller from a Raspberry Pi or NVIDIA Jetson, use the Python/VNH5019Controller
library. You can use both I2C and Serial, however USB serial is likely the simplest option as it allows
you to provide both power and communication to the controller over a single wire. An example sketch has
been provided in PythonExample/PythonExample.py.


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
