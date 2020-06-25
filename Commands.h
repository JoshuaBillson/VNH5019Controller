#ifndef COMMANDS_H
#define COMMANDS_H

#include "Arduino.h"

#define CONTROLLER_ADDRESS 0x1
#define BAUDRATE 115200

#define VALUE_MIN -100
#define VALUE_MAX 100
#define DRIVER_MAX 400
#define BYTE_MAX 255

/* Command Bit Indexes */
#define CHANNEL_1_BIT 7
#define CHANNEL_2_BIT 6
#define SPEED_BIT 5
#define BRAKE_BIT 4
#define MIXED_BIT 3
#define TOGGLE_STATE_BIT 2


/* Command Bits */
#define CHANNEL_1 B10000000
#define CHANNEL_2 B01000000
#define SPEED B00100000
#define BRAKE B00010000
#define MIXED B00001000
#define TOGGLE_STATE B00000100

/* Recognized Commands */
enum Commands {
    SET_CHANNEL_1_SPEED = (CHANNEL_1 | SPEED),
    SET_CHANNEL_2_SPEED = (CHANNEL_2 | SPEED),
    SET_BOTH_CHANNEL_SPEED = ((CHANNEL_1 | CHANNEL_2) | SPEED),
    BRAKE_CHANNEL_1 = (CHANNEL_1 | BRAKE),
    BRAKE_CHANNEL_2 = (CHANNEL_2 | BRAKE),
    BRAKE_BOTH_CHANNELS = ((CHANNEL_1 | CHANNEL_2) | BRAKE),
    MIXED_COMMAND = MIXED,
    TOGGLE_STATE_COMMAND = TOGGLE_STATE,
};

/* Error Codes */
enum Error {
    COMMAND_RECEIVED,
    INVALID_COMMAND,
    CHANNEL_1_ERROR,
    CHANNEL_2_ERROR,
    FATAL_ERROR,
};

/* Motor Driver State */
enum State {
    STANDBY,
    ACTIVE,
};

#endif
