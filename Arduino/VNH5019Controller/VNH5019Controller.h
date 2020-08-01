#ifndef VNH5019_CONTROLLER_H
#define VNH5019_CONTROLLER_H

#include <Arduino.h>

/* Methods For Writing To The Controller */
enum WriteMode {
    I2C,
    SRL /* Note: The Macro "SERIAL" Is Defined In "Arduino.h" */
};

/* Motor Channels Which Can Be Set On The Controller */
enum Channels {
    ONE,
    TWO,
    BOTH
};


/* A Class Representing An Arduino Uno Equipped With A Dual VNH5019 Motor Shield */
class VNH5019_Controller {

    public:

    /*
     * Open I2C and Serial Ports For Writing To The Controller; Called In setup()
     * --------------------------------------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     */
    void mount(WriteMode mode);

    /*
     * Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels
     * ------------------------------------------------------------------------------------
     * channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)
     * value: The Value We Want To Write
     */
    void writeSpeed(Channels channel, int8_t value);

    /*
     * Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels
     * -------------------------------------------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     * channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)
     * value: The Value We Want To Write
     */
    void writeBrake(Channels channel, byte value);

    /*
     * Write A Mixed Command
     * ---------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     * speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward)
     * turnVal: A Value From -100 (Full Left) To 100 (Full Right)
     */
    void writeMixedCommand(int8_t speedVal, int8_t turnVal);

    /*
     * Stop Both Motors By Applying Maximum Braking
     * --------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     */
    void stop();

    /*
     * Place The Controller Into An Active State
     * -----------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     */
    void setActive();

    /*
     * Place The Controller Into Standby
     * ---------------------------------
     * writeMode: The Method Of Communication, Either I2C or SRL
     */
    void setStandby();

    private:

    int writeMode;

    static void writeI2C(byte* bytes, byte numBytes);

    static void writeSerial(byte* bytes, byte numBytes);

    void (*WriteFunctions[2])(byte*, byte) = {VNH5019_Controller::writeI2C, VNH5019_Controller::writeSerial};

};

#endif
