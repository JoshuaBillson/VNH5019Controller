"""
An example program utilizing the Controller class to write both standard and mixed commands over USB Serial.
"""
import VNH5019Controller
from time import sleep
from sys import argv

assert len(argv) > 1, "Error: Serial Port Must Be Specified!"
assert len(argv) < 3, "Error: Too Many Arguments Passed!"

controller = VNH5019Controller.Controller()


def setup():
    print("Setting Up...")
    VNH5019Controller.init_serial(argv[1])
    sleep(5)
    controller.set_active()
    sleep(2)
    print("Ready!")


def loop():
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
    while True:
        loop()


if __name__ == '__main__':
    main()