# VNH5019Controller Python Library
This library provides the Controller class to generate valid messages and communicate with the 
motor controller via either I2C or USB. Before any commands can be sent, the functions **init_serial()**
or **init_i2c()** must be called. The constants **CHANNEL_1**, **CHANNEL_2**, and **BOTH** are passed to
**Controller.write_speed()** and **Controller.write_brake()** to select the appropriate channel.

# Installation
```
pip install VNH5019-Serial-Controller
```

# Classes:
### Controller
A class for writing to the VNH5019 Motor Controller via either I2C or USB.

# Constants:
#### CHANNEL_1
#### CHANNEL_2
#### BOTH

# Functions:

### init_serial( port_name )

Initialize a serial port for communication with the motor controller.  

##### port_name 
Type: `string`  

The name of the serial port to communicate over.  

##### Returns
Type: `None`  

### init_i2c( pre_existing_bus=None )

Initialize the serial bus for communication.  

##### pre_existing_bus

Type: `SMBus`  

Default: `None`  

A pre-existing I2C bus if it exists.  

##### Returns

Type: `None`  

# Controller Methods

### write_speed( channel, value )

Write a speed value between -100 (full reverse) to 100 (full forward) to one or both channels.  

##### channel

Type: `int`  

The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.  

##### value

Type: `int`  

The speed we want to set between -100 to 100.  

##### Returns

Type: `None`  

### write_brake( channel, value )

Write a brake value between 0 (coast) to 100 (max brake) to one or both channels.  

##### channel

Type: `int`  

The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.  

##### value

Type: `int`  

The brake we want to set between 0 to 100.  

##### Returns

Type: `None`  

### write_mixed_command( speed_val, turn_val )

Write a mixed command to the motor controller.  

##### speed_val 

Type: `int`  

The speed we want to write between -100 (full reverse) to 100 (full forward).  

##### turn_val 

Type: `int`  

The turn value we want to write between -100 (max left) to 100 (max right).  

##### Returns

Type: `None`  

### stop()

Stop both motors by applying max brakes.  

##### Returns

Type: `None`  

### set_active()

Put the motor controller into an active state.  

##### Returns

Type: `None`  

### set_standby()

Put the motor controller into standby.  

##### Returns

Type: `None`  

# Example
```python
import VNH5019Controller
from time import sleep
from sys import argv

controller = VNH5019Controller.Controller()


def setup():
    print("Setting Up...")
    VNH5019Controller.init_serial(argv[1])
    sleep(5)
    controller.set_active()
    sleep(2)
    print("Ready!")


def loop():
    while True:
        # Drive Forward
        print("Forward")
        controller.write_speed(VNH5019Controller.BOTH, 100)
        sleep(1)
        controller.stop()
        sleep(1)

        # Drive Backward
        print("Backward")
        controller.write_speed(VNH5019Controller.BOTH, -100)
        sleep(1)
        controller.stop()
        sleep(1)

        # Turn Left Forward
        print("Forward Left")
        controller.write_mixed_command(100, -50)
        sleep(1)
        controller.stop()
        sleep(1)

        # Turn Right Forward
        print("Forward Right")
        controller.write_mixed_command(100, 50)
        sleep(1)
        controller.stop()
        sleep(1)

        # Turn Left Backward
        print("Backward Left")
        controller.write_mixed_command(-100, -50)
        sleep(1)
        controller.stop()
        sleep(1)

        # Turn Right Backward
        print("Backward Right")
        controller.write_mixed_command(-100, 50)
        sleep(1)
        controller.stop()
        sleep(1)

        # Enter Standby
        print("Entering Standby...")
        controller.set_standby()
        sleep(5)

        # Enter Active
        print("Entering Active...")
        controller.set_active()
        sleep(2)


def main():
    setup()
    loop()


if __name__ == '__main__':
    main()
```
