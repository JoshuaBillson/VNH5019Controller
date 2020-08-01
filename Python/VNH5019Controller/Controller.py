import VNH5019Controller.Commands as Commands
from serial import Serial

try:
    from smbus2 import SMBus
except ImportError:
    print("smbus2 Not Installed. Couldn't Configure I2C.")

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
    global ser
    ser = Serial(port_name, BAUDRATE)


def init_i2c(pre_existing_bus=None):
    global bus
    if pre_existing_bus is not None:
        bus = pre_existing_bus
    else:
        bus = SMBus(1)


def write_serial(bytes_to_write):
    assert type(bytes_to_write) == bytes, "Error: Invalid Data Type!"
    global ser
    assert ser is not None, "Error: Serial Port Is Not Initialized!"
    ser.write(bytes_to_write)


def write_i2c(bytes_to_write):
    assert type(bytes_to_write) == bytes, "Error: Invalid Data Type!"
    global bus
    assert bus is not None, "Error: I2C Bus Is Not Initialized!"
    bus.write_i2c_block_data(Commands.CONTROLLER_ADDRESS, 0, list(bytes_to_write))


class VNH5019Controller:
    def __init__(self):
        pass

    def write_speed(self, channel, value, write_method=None):
        assert channel == CHANNEL_1 or channel == CHANNEL_2 or channel == BOTH, "Write Error: Invalid Channel!"
        assert -100 <= value <= 100, "Write Error: Invalid Value!"
        commands = (Commands.SET_CHANNEL_1_SPEED, Commands.SET_CHANNEL_2_SPEED, Commands.SET_BOTH_CHANNEL_SPEED)
        bytes_to_write = self._to_byte_array((commands[channel], value))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    def write_brake(self, channel, value, write_method=None):
        assert channel == CHANNEL_1 or channel == CHANNEL_2 or channel == BOTH, "Write Error: Invalid Channel!"
        assert value <= 100, "Write Error: Invalid Value!"
        commands = (Commands.BRAKE_CHANNEL_1, Commands.BRAKE_CHANNEL_2, Commands.BRAKE_BOTH_CHANNELS)
        bytes_to_write = self._to_byte_array((commands[channel], value))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    def write_mixed_command(self, speed_val, turn_val, write_method=None):
        assert -100 <= speed_val <= 100, "Write Error: Invalid Value!"
        assert -100 <= turn_val <= 100, "Write Error: Invalid Value!"
        bytes_to_write = self._to_byte_array((Commands.MIXED_COMMAND, speed_val, turn_val))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    def stop(self, write_method=None):
        bytes_to_write = self._to_byte_array((Commands.BRAKE_BOTH_CHANNELS, 100))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    def set_active(self, write_method=None):
        bytes_to_write = self._to_byte_array((Commands.TOGGLE_STATE_COMMAND, Commands.ACTIVE))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    def set_standby(self, write_method=None):
        bytes_to_write = self._to_byte_array((Commands.TOGGLE_STATE_COMMAND, Commands.STANDBY))
        if write_method is not None:
            write_method(bytes_to_write)
        return bytes_to_write

    @staticmethod
    def _to_byte(number, is_signed):
        return number.to_bytes(1, byteorder='big', signed=is_signed)

    @staticmethod
    def _to_byte_array(numbers):
        byte_array = []
        for x in numbers:
            if x < 0:
                byte_array.append(VNH5019Controller._to_byte(x, True))
            else:
                byte_array.append(VNH5019Controller._to_byte(x, False))
        return b''.join(byte_array)
