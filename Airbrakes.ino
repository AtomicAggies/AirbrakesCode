// Global_Variables
// by Preston Hager

#include "ESP32Servo.h"
#include "MS5611.h"
#include "MPU6050.h"
#include "I2Cdev.h"
#include "SimpleKalmanFilter.h"
#include <heltec.h>
#include <SPI.h>
#include <SD.h>

// ========== Can Change ========== //
// Change these variables to influence program parameters

// Verbose logging level
// 0 - no logging
// 1 - info logging only
// 2 - debug logging
// 3 - all logging
const int verboseLevel = 3;

// Servo opening and closing values
// These can be from -90 to 90
// NOTE: values may need to be refined
const int servoOpeningValue = 0;
const int servoClosingValue = 90;

// Servo pin on the board
// Recommended pins are 2, 4, 15-18, 21-23, 25-27, 32-33
const int servoPin = 15;

// Buzzer pin
const int buzzerPin = 13;

// SD Chip Select
// By default this is 18 on the Heltec LoRa 32(V2)
// It may be different for other boards though
// Usually it's the default slave select (SS) pin
const int SDChipSelect = 21;

// Servo movment speed
// Values between 0 and 2000
// The higher the number, the faster the servo will step to its written value
const int minUS = 1000;
const int maxUS = 2000;

// Type of Activation
// If you want to either use Pressure, G-Force, or both
// for the method of activating the airbrakes
// Value is binary with each byte representing to use the activation
// Byte 1 is Pressure activation (use 0b00000001)
// Byte 2 is G-Force activation  (use 0b00000010)
// for both types use 0b00000011
const int activationType = 0b00000001;

// G-Force activation value
// Values from 0 to infinity
// 10000 is for 4Gs
// This is the G-Force point at which the airbrakes will open
const float GForceActivation = 8000;
// Pressure activation value
// Values are from -infinity to infinity measured in millibars
const float PressureActivation = 160;

// ========== Do Not Change ========== //
// Do not change these variables, they are used by the program

Servo servo;
ESP32PWM pwm;
MPU6050 accelgyro;

int16_t uprightX, uprightZ;
bool servosOpened = false;

// NOTE: depending on wiring the this may need to be either 0x77 or 0x76
//       see https://forum.arduino.cc/t/need-help-to-connect-ms5611-pressure-sensor-in-i2c-mode/341813
MS5611 ms5611 = MS5611(0x77);
double referencePressure;

// SimpleKalmanFilter(e_mea, e_est, q);
// e_mea: Measurement Uncertainty
// e_est: Estimation Uncertainty
// q: Process Noise
SimpleKalmanFilter gyroKalmanFilter(1, 1, 1);
SimpleKalmanFilter accelKalmanFilter(1, 1, .001);

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif