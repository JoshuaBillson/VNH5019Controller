/*
 * Project: VNH5019 Controller Firmware
 * Author: Joshua Billson
 *
 * This program constitutes the firmware uploaded to an Arduino Uno coupled with a Dual VNH5019
 * Motor Shield. The intent is to provide a means of external control via both TTL serial and I2C
 * to set the speed, direction, and braking of up to two independent motor channels.
 *
 * The controller can be operated both in "standard" and "mixed" mode. Standard mode allows us to
 * manually set each parameter (speed, direction, brake) independently for each motor channel by
 * writing a two byte message where the first byte denotes which channel and setting we wish to
 * write while the second encodes the corresponding value. Mixed mode is intended primarily for
 * controlling differential drive vehicles and consists of three bytes: a command byte, a speed
 * byte, and a turn byte. The command byte simply denotes that we are sending a mixed instruction
 * while the speed byte encodes speed with a value between -100 (full reverse) to 100 (full forward)
 * and the turn byte encodes turning with -100 corresponding to full left, 100 full right, and 0 as
 * straight ahead.
 */

#include "DualVNH5019MotorShield.h"
#include "Commands.h"
#include "Notes.h"
#include <Wire.h>

#define LED_PIN 5
#define BUZZER_PIN 13

/*
 * If This Length Of Time (in ms) Passes Between Received Instructions, Controller
 * Enters Standby As It Is Assumed Connection To The Master Has Been Lost.
 */
#define TIMEOUT 15000 /* Length Of Time In Milliseconds */

volatile uint64_t lastInstruction = 0;

volatile byte state = STANDBY;
volatile bool toggleActive = false;
volatile bool toggleStandby = false;

volatile int motorOneSpeed = 0;
volatile int motorTwoSpeed = 0;

volatile int motorOneBrake = 0;
volatile int motorTwoBrake = 0;

DualVNH5019MotorShield motorDriver;


void setup() {
  Serial.begin(BAUDRATE);

  motorDriver.init();
  stopIfFault();

  Wire.begin(CONTROLLER_ADDRESS);
  Wire.onReceive(receiveEvent);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  analogWrite(LED_PIN, BYTE_MAX);
  powerUpChime();
}


void loop() {
  while (state == STANDBY) {
    enterStandby();
    pulseLED();
  }

  while (state == ACTIVE) {
    if ((millis() - lastInstruction) > TIMEOUT) {
      state = STANDBY;
      toggleStandby = true;
    } else {
      enterActive();
      setMotors();
    }
  }
}


/* This Function Is Called Whenever A Transmission Is Received On I2C. */
void receiveEvent(int numBytes) {
  lastInstruction = millis();

  byte command = readByte();

  if (command == MIXED_COMMAND) {
    int8_t speedVal = readByte();
    int8_t turnVal = readByte();
    handleMixedCommand(speedVal, turnVal);
  } else {
    int8_t value = readByte();
    handleStandardCommand(command, value);
  }
}


/* This Function Is Called Whenever A Transmission Is Received Over Serial. */
void serialEvent() {
  lastInstruction = millis();

  byte command = readByteSerial();

  if (command == MIXED_COMMAND) {
    int8_t speedVal = readByteSerial();
    int8_t turnVal = readByteSerial();
    handleMixedCommand(speedVal, turnVal);
  } else {
    int8_t value = readByteSerial();
    handleStandardCommand(command, value);
  }
}


/* Receives and Handles a Mixed 3-Byte Command. */
void handleMixedCommand(const int8_t speedVal, int8_t turnVal) {
  motorOneSpeed = speedVal;
  motorTwoSpeed = speedVal;

  turnVal *= (speedVal < 0) ? -1 : 1; /* Flip turnVal If Driving In Reverse. */

  /* Handle The Case Where Turning Left */
  while (turnVal < 0) {
    if (motorOneSpeed > VALUE_MIN) {
      motorOneSpeed--;
      turnVal++;
    }

    if ((motorTwoSpeed < VALUE_MAX) && (turnVal < 0)) {
      motorTwoSpeed++;
      turnVal++;
    }
  }

  /* Handle The Case Where Turning Right */
  while (turnVal > 0) {
    if (motorOneSpeed < VALUE_MAX) {
      motorOneSpeed++;
      turnVal--;
    }

    if ((motorTwoSpeed > VALUE_MIN) && (turnVal > 0)) {
      motorTwoSpeed--;
      turnVal--;
    }
  }

  /* Apply Moderate Braking In The Event That Motor Speed Is Zero */
  motorOneBrake = (motorOneSpeed == 0) ? (VALUE_MAX / 2): 0;
  motorTwoBrake = (motorTwoSpeed == 0) ? (VALUE_MAX / 2): 0;
}


/* Receives and Handles a Standard 2-Byte Command. */
void handleStandardCommand(const byte command, const int8_t value) {
  /* Set Driver State To Either Active Or Standby. */
  if (command == TOGGLE_STATE_COMMAND) {
    toggleActive = (state == STANDBY && value == ACTIVE) ? true : false;
    toggleStandby = (state == ACTIVE && value == STANDBY) ? true : false;
    state = value;
  }

  /* Note: Setting Speed Overrides Braking and Vice-Versa. */

  /* Set Brake or Speed For Channel 1 */
  if (bitRead(command, CHANNEL_1_BIT) && state == ACTIVE) {
    if (bitRead(command, SPEED_BIT)) {
      motorOneSpeed = value;
      motorOneBrake = 0;
    } else if (bitRead(command, BRAKE_BIT)) {
      motorOneBrake = value;
      motorOneSpeed = 0;
    }
  }

  /* Set Brake or Speed For Channel 2 */
  if (bitRead(command, CHANNEL_2_BIT) && state == ACTIVE) {
    if (bitRead(command, SPEED_BIT)) {
      motorTwoSpeed = value;
      motorTwoBrake = 0;
    } else if (bitRead(command, BRAKE_BIT)) {
      motorTwoBrake = value;
      motorTwoSpeed = 0;
    }
  }
}


/* Execute Braking Or Speed Control Parameters Via Calls To motorDriver */
void setMotors() {
  /* Motor One */
  if (motorOneBrake != 0) {
    motorDriver.setM1Brake(motorOneBrake * 4);
  } else {
    motorDriver.setM1Speed(motorOneSpeed * 4);
  }

  /* Motor Two */
  if (motorTwoBrake != 0) {
    motorDriver.setM2Brake(motorTwoBrake * 4);
  } else {
    motorDriver.setM2Speed(motorTwoSpeed * 4);
  }
}


/* Read a Single Byte Over I2C. If No Byte Is Available, Returns A Default of Zero. */
byte readByte() {
  if (Wire.available()) {
    return Wire.read();
  }
  return 0;
}


/* Read a Single Byte Over Serial. If No Byte Is Available, Returns A Default of Zero. */
byte readByteSerial() {
  if (Serial.available()) {
    return Serial.read();
  }
  return 0;
}


/* Regulate The Brightness Of an LED With Respect To Time According To A Cosine-Squared Function. */
void pulseLED() {
    static const float period = 2000.0;
    static const float pi = 3.14;
    float cosine = cos((float(millis()) * pi) / period); /* Repeats Every 2000 Milliseconds. */
    float consineSquared = (cosine * cosine);
    byte brightness = consineSquared * float (BYTE_MAX);
    analogWrite(LED_PIN, brightness);
}


/* Play A Power-Up Chime */
void powerUpChime() {
    playNote(BUZZER_PIN, A, 100);
    playNote(BUZZER_PIN, CS, 100);
    playNote(BUZZER_PIN, E, 250);
}


/* Play A Chime Indicating A Transition To An Active State */
void activeChime() {
    playNote(BUZZER_PIN, E, 200);
    playNote(BUZZER_PIN, A, 200);
    playNote(BUZZER_PIN, CS, 200);
    playNote(BUZZER_PIN, E, 200);
}


/* Play A Chime Indicating A Transition To A Passive State */
void standbyChime() {
    playNote(BUZZER_PIN, E, 200);
    playNote(BUZZER_PIN, A, 200);
}


/* This Procedure Runs When Entering An Active State From A Passive State */
void enterActive() {
  if (toggleActive) {
    activeChime();
    analogWrite(LED_PIN, BYTE_MAX);
    toggleActive = false;
  }
}


/* This Procedure Runs When Entering A Passive State From An Active State */
void enterStandby() {
  if (toggleStandby) {
    motorOneSpeed = 0;
    motorTwoSpeed = 0;
    motorDriver.setBrakes(motorOneBrake = DRIVER_MAX, motorTwoBrake = DRIVER_MAX);
    standbyChime();
    toggleStandby = false;
  }
}


/* Halts The Program In The Event Of An Error In Motor One Or Two */
void stopIfFault() {
  if (motorDriver.getM1Fault() || motorDriver.getM2Fault()) {
    Serial.println("Motor Fault!");
    while(1);
  }
}
