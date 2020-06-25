#ifndef VNH5019_CONTROLLER_H
#define VNH5019_CONTROLLER_H

#include <Arduino.h>
#include "Commands.h"

/* Methods For Writing To The Controller */
enum WriteMode {
    I2C,
    SERIAL
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
     * Takes No Arguments And Returns Nothing
     */
    void mount();

    /*
     * Write A Speed From -100 (full reverse) to 100 (full forward) To One Or Both Channels
     * ------------------------------------------------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     * channel: The Channel Whose Speed We Want To Set (ONE, TWO, or BOTH)
     * value: The Value We Want To Write
     */
    void writeSpeed(byte writeMode, byte channel, int8_t value);

    /*
     * Write A Brake Value From 0 (coast) to 100 (full brake) To One Or Both Channels
     * -------------------------------------------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     * channel: The Channel Whose Brakes We Want To Set (ONE, TWO, or BOTH)
     * value: The Value We Want To Write
     */
    void writeBrake(byte writeMode, byte channel, byte value);

    /*
     * Write A Mixed Command
     * ---------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     * speedVal: A Value From -100 (Full Reverse) To 100 (Full Forward)
     * turnVal: A Value From -100 (Full Left) To 100 (Full Right)
     */
    void writeMixedCommand(byte writeMode, int8_t speedVal, int8_t turnVal);

    /*
     * Stop Both Motors By Applying Maximum Braking
     * --------------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     */
    void stop(byte writeMode);

    /*
     * Place The Controller Into An Active State
     * -----------------------------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     */
    void setActive(byte writeMode);

    /*
     * Place The Controller Into Standby
     * ---------------------------------
     * writeMode: The Method Of Communication, Either I2C or SERIAL
     */
    void setStandby(byte writeMode);

};

#endif
