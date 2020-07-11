# VNH5019 Controller

## Overview

The purpose of this project is to provide a means of controlling a [Dual VNH5019 Motor Driver
Shield](https://www.pololu.com/product/2507) coupled with an Arduino Uno from an external device over
either I2C or serial. This project uses the standard serial port for the receiving Arduino; to use other hardware serial ports
(Serial1, Serial2, etc.) or Software Serial requires modification to the source code.


## Dependencies

This project makes use of the [DualVNH5019MotorShield library](https://github.com/pololu/dual-vnh5019-motor-shield)
for the firmware running on the Uno Controller and must be installed to you Arduino/libraries
folder.


## Audio-Visual Feedback And Wiring

LED and Audio feedback denoting the state of the controller has been included in the firmware. When
the controller first powers up, a start-up chime will play and an LED will light up. Whilst the controller
is in standby, the LED will blink at regular 2 second intervals and will be solid when the controller
is active. Additionally, a unique chime will play when the controller enters a standby state and when
it enters an active state. Use of this feature is optional, but please be aware that the led is controlled
by digital pin 5 and the piezo buzzer is controlled by digital pin 13. Please refer to "VNH5019_Controller_Schematic.pdf"
for further wiring information.


## Usage

In order to control the Arduino Uno / VNH5019 Motor Driver Shield from an external device, the corresponding
firmware found in Firmware/Firmware.ino must be uploaded to the receiving Arduino. In theory, any programmable
device capable of communicating with an Arduino over I2C or Serial should be capable of interfacing with
this motor controller. However, this project was designed with other Arduinos, Raspberry Pis, and NVIDIA
Jetson's in mind. Should you need to extend this project to unsupported devices, the complete set of
recognized codes used to control the Arduino Uno / VNH5019 Motor Controller is included in "Commands.h".
To interface with the motor controller over either serial or I2C from an external device, use the
VNH5019_Controller class and associated methods.


## Arduino

To interface with the motor controller from an Arduino compatible board, use the Arduino/VNH5019Controller
library. An example sketch has been provided in ArduinoExample/ArduinoExample.ino. You can use both I2C
and Serial, however I2C is likely the preferred option for interfacing two Arduinos. Please note that
Serial1, Serial2, etc. and SoftwareSerial is not supported.


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
