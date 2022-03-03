// Global_Variables
// by Preston Hager

#include "ESP32Servo.h"
#include "MS5611.h"
#include "MPU6050.h"
#include "I2Cdev.h"
#include "SimpleKalmanFilter.h"
#include <SPI.h>
#include <SD.h>
#include <esp_now.h>
#include <WiFi.h>

// ========== Can Change ========== //
// Change these variables to influence program parameters

// Pins for the SD card
// Note that these must be different than
// the SPI pins already in use by the LoRa.
#define SD_CS 2
#define SD_SCK 17
#define SD_MOSI 23
#define SD_MISO 13

bool SD_Init = false;

// Verbose logging level
// 0 - no logging
// 1 - info logging only
// 2 - debug logging
// 3 - all logging
const int verboseLevel = 3;
#define VERBOSE_LEVEL 3

// Servo opening and closing values
// These can be from -90 to 90
// NOTE: values may need to be refined
//const int servoOpeningValue = 0;
//const int servoClosingValue = 90;
#define SERVO_OPEN  0
#define SERVO_CLOSE 90

// Servo pin on the board
// Recommended pins are 2, 4, 15-18, 21-23, 25-27, 32-33
//const int servoPin = 15;
#define SERVO_PIN   15

// Buzzer pin
const int buzzerPin = 12;

// SD Chip Select
// By default this is 18 on the Heltec LoRa 32(V2)
// It may be different for other boards though
// Usually it's the default slave select (SS) pin
//const int SDChipSelect = 21;

// Servo movment speed
// Values between 0 and 2000
// The higher the number, the faster the servo will step to its written value
const int minUS = 1000;
const int maxUS = 2000;

// Pressure activation value
// Values are from -infinity to infinity measured in millibars
//const float PressureActivation = 160;
#define PRESSURE_ACTIVATION   890

// Tilt Threshold
// When to close the flaps, after the rocket has tilted over on the x/z axis
// by a certain value.
// Values from 0-360 in degrees.
//const int TiltThreshold = 40;
#define TiltThreshold   40

// MAC Address of the WiFi reciever
// This is used for the avionics data sending
// The MAC address of the black box
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x5F, 0x3B, 0xEC};

// ========== Do Not Change ========== //
// Do not change these variables, they are used by the program

Servo servo;
ESP32PWM pwm;
MPU6050 accelgyro;

int16_t uprightX, uprightZ;
bool servosOpened = false;

// WiFi peer information
esp_now_peer_info_t peerInfo;

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
