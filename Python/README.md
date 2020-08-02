# VNH5019Controller Python Library

## Summary
This library provides the Controller class to generate valid messages and communicate with the 
motor controller via either I2C or USB. Before any commands can be sent, the functions **init_serial()**
or **init_i2c()** must be called. The constants **CHANNEL_1**, **CHANNEL_2**, and **BOTH** are passed to
**Controller.write_speed()** and **Controller.write_brake()** to select the appropriate channel.

## Classes:
**Controller**  
A class for writing to the VNH5019 Motor Controller via either I2C or USB.

## Constants:
**CHANNEL_1**  
**CHANNEL_2**  
**BOTH**  

## Functions:
**init_serial(port_name)**  
Initialize a serial port for communication with the motor controller.  
port_name (string): The name of the serial port to communicate over.  

**init_i2c(pre_existing_bus=None)**  
Initialize the serial bus for communication.  
pre_existing_bus (SMBus): A pre-existing I2C bus if it exists.  

**Controller.write_speed(channel, value)**  
Write a speed value between -100 (full reverse) to 100 (full forward) to one or both channels.  
channel (int): The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.  
value (int): The speed we want to set between -100 to 100.  
Returns (bytes): The bytes to be written to the controller.  

 **Controller.write_brake(channel, value)**
Write a brake value between 0 (coast) to 100 (max brake) to one or both channels.  
channel (int): The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.  
value (int): The brake we want to set between 0 to 100.  
Returns (bytes): The bytes to be written to the controller.  

**Controller.write_mixed_command(speed_val, turn_val)**
Write a mixed command to the motor controller.  
speed_val (int): The speed we want to write between -100 (full reverse) to 100 (full forward).  
turn_val (int): The turn value we want to write between -100 (max left) to 100 (max right).  
Returns (bytes): The bytes to be written to the controller.  

**Controller.stop()**
Stop both motors by applying max brakes.  
Returns (bytes): The bytes to be written to the controller.  

**Controller.set_active()**
Put the motor controller into an active state.  
Returns (bytes): The bytes to be written to the controller.  

**Controller.set_standby()**
Put the motor controller into standby.  
Returns (bytes): The bytes to be written to the controller.  
