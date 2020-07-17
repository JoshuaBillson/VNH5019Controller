import serial
import commands

I2C = 0
SRL = 1

class VNH5019Controller:
    def __init__(self, mode, port = None):
        assert mode == I2C or mode == SRL, "Initialization Error: Mode Must Be Either I2C or SRL!"
        self.mode = mode
        if mode == SRL:
            assert port != None, "Initialization Error: Must Specify A Port For Serial Communication!"
            self.port = port

    def _transmit
