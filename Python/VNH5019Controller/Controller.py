"""
This file defines the Controller class for communicating with the VNH5019 Motor Controller.
"""
import VNH5019Controller.Commands as Commands
from serial import Serial

# Import smbus2 if it exists in the present environment.
try:
    from smbus2 import SMBus
except ImportError:
    pass

# Enumeration For Writing Standard Commands
CHANNEL_1 = 0
CHANNEL_2 = 1
BOTH = 2

# Serial Baudrate
BAUDRATE = 115200

# Global Variables For The I2C Port (bus) and Serial Port (ser)
bus = None
ser = None


def init_serial(port_name):
    """
    Initialize a serial port for communication with the motor controller, must be called prior to
    writing to the controller.

    port_name (string): The name of the USB port over which we wish to communicate.

    Returns: None.
    """
    global ser
    ser = Serial(port_name, BAUDRATE)


def init_i2c(pre_existing_bus=None):
    """
    Initialize the serial bus for communication. Must be called prior to communicating with the controller via I2C.

    pre_existing_bus (SMBus): A pre-existing bus if it exists.

    Returns: None.
    """
    global bus
    if pre_existing_bus is not None:
        bus = pre_existing_bus
    else:
        bus = SMBus(1)


class Controller:
    """
    Provides methods for controlling the motor controller via either I2C or USB Serial communication.
    """
    def __init__(self):
        pass

    def write_speed(self, channel, value):
        """
        Write a speed value between -100 (full reverse) to 100 (full forward) to one or both channels.

        channel (int): The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.
        value (int): The speed we want to set between -100 to 100.
        """
        global ser, bus
        assert channel == CHANNEL_1 or channel == CHANNEL_2 or channel == BOTH, "Write Error: Invalid Channel!"
        assert -100 <= value <= 100, "Write Error: Invalid Value!"
        commands = (Commands.SET_CHANNEL_1_SPEED, Commands.SET_CHANNEL_2_SPEED, Commands.SET_BOTH_CHANNEL_SPEED)
        bytes_to_write = self._to_byte_array((commands[channel], value))
        Controller._write_bytes(bytes_to_write)

    def write_brake(self, channel, value):
        """
        Write a brake value between 0 (coast) to 100 (max brake) to one or both channels.

        channel (int): The channel whose speed we want to set. Must be one of CHANNEL_1, CHANNEL_2, or BOTH.
        value (int): The brake we want to set between 0 to 100.
        """
        assert channel == CHANNEL_1 or channel == CHANNEL_2 or channel == BOTH, "Write Error: Invalid Channel!"
        assert value <= 100, "Write Error: Invalid Value!"
        commands = (Commands.BRAKE_CHANNEL_1, Commands.BRAKE_CHANNEL_2, Commands.BRAKE_BOTH_CHANNELS)
        bytes_to_write = self._to_byte_array((commands[channel], value))
        Controller._write_bytes(bytes_to_write)

    def write_mixed_command(self, speed_val, turn_val):
        """
        Write a mixed command to the motor controller.

        speed_val (int): The speed we want to write between -100 (full reverse) to 100 (full forward).
        turn_val (int): The turn value we want to write between -100 (max left) to 100 (max right).
        """
        assert -100 <= speed_val <= 100, "Write Error: Invalid Value!"
        assert -100 <= turn_val <= 100, "Write Error: Invalid Value!"
        bytes_to_write = self._to_byte_array((Commands.MIXED_COMMAND, speed_val, turn_val))
        Controller._write_bytes(bytes_to_write)

    def stop(self):
        """Stop both motors by applying max brakes."""
        bytes_to_write = self._to_byte_array((Commands.BRAKE_BOTH_CHANNELS, 100))
        Controller._write_bytes(bytes_to_write)

    def set_active(self):
        """Put the motor controller into an active state."""
        bytes_to_write = self._to_byte_array((Commands.TOGGLE_STATE_COMMAND, Commands.ACTIVE))
        Controller._write_bytes(bytes_to_write)

    def set_standby(self):
        """Put the motor controller into standby."""
        bytes_to_write = self._to_byte_array((Commands.TOGGLE_STATE_COMMAND, Commands.STANDBY))
        Controller._write_bytes(bytes_to_write)

    # PRIVATE METHODS - DO NOT TOUCH THESE!
    @staticmethod
    def _write_bytes(bytes_to_write):
        if ser is not None:
            Controller._write_serial(bytes_to_write)
        elif bus is not None:
            Controller._write_i2c(bytes_to_write)

    @staticmethod
    def _write_i2c(bytes_to_write):
        assert type(bytes_to_write) == bytes, "Error: Invalid Data Type!"
        global bus
        assert bus is not None, "Error: I2C Bus Is Not Initialized!"
        bus.write_i2c_block_data(Commands.CONTROLLER_ADDRESS, 0, list(bytes_to_write))

    @staticmethod
    def _write_serial(bytes_to_write):
        assert type(bytes_to_write) == bytes, "Error: Invalid Data Type!"
        global ser
        assert ser is not None, "Error: Serial Port Is Not Initialized!"
        ser.write(bytes_to_write)

    @staticmethod
    def _to_byte(number, is_signed):
        return number.to_bytes(1, byteorder='big', signed=is_signed)

    @staticmethod
    def _to_byte_array(numbers):
        byte_array = []
        for x in numbers:
            if x < 0:
                byte_array.append(Controller._to_byte(x, True))
            else:
                byte_array.append(Controller._to_byte(x, False))
        return b''.join(byte_array)
