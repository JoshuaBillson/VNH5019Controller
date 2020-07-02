#include <Arduino.h>
#include <Wire.h>
#include "Commands.h"
#include "VNH5019Controller.h"

#define NUM_STANDARD_BYTES 2
#define NUM_MIXED_BYTES 3


void VNH5019_Controller::mount() {
    Serial.begin(BAUDRATE);
    Wire.begin(); /* Join I2C Bus As Master */
}


void VNH5019_Controller::writeSpeed(WriteMode mode, Channels channel, int8_t value) {
    /* Index These Arrays To Choose Mode Of Transmission And Command */
    static byte commands[3] = {SET_CHANNEL_1_SPEED, SET_CHANNEL_2_SPEED, SET_BOTH_CHANNEL_SPEED};

    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_STANDARD_BYTES] = {commands[channel], value};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_STANDARD_BYTES);
}


void VNH5019_Controller::writeBrake(WriteMode mode, Channels channel, byte value) {
    /* Index These Arrays To Choose Mode Of Transmission And Command */
    static byte commands[3] = {BRAKE_CHANNEL_1, BRAKE_CHANNEL_2, BRAKE_BOTH_CHANNELS};

    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_STANDARD_BYTES] = {commands[channel], value};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_STANDARD_BYTES);
}


void VNH5019_Controller::writeMixedCommand(WriteMode mode, int8_t speedVal, int8_t turnVal) {
    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_MIXED_BYTES] = {MIXED_COMMAND, speedVal, turnVal};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_MIXED_BYTES);
}


void VNH5019_Controller::stop(WriteMode mode) {
    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_STANDARD_BYTES] = {BRAKE_BOTH_CHANNELS, VALUE_MAX};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_STANDARD_BYTES);
}


void VNH5019_Controller::setActive(WriteMode mode) {
    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_STANDARD_BYTES] = {TOGGLE_STATE_COMMAND, ACTIVE};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_STANDARD_BYTES);
}


void VNH5019_Controller::setStandby(WriteMode mode) {
    /* Prepare The Bytes To Be Transmitted */
    byte bytes[NUM_STANDARD_BYTES] = {TOGGLE_STATE_COMMAND, STANDBY};

    /* Tansmit */
    WriteFunctions[mode](bytes, NUM_STANDARD_BYTES);
}


static void VNH5019_Controller::writeI2C(byte* bytes, byte numBytes) {
    Wire.beginTransmission(CONTROLLER_ADDRESS);
    Wire.write(bytes, numBytes);
    Wire.endTransmission();
}


static void VNH5019_Controller::writeSerial(byte* bytes, byte numBytes) {
    Serial.write(bytes, numBytes);
}
