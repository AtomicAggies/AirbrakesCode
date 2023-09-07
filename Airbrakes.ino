// Global_Variables

//#include <ESP32Servo.h>
#include <Servo.h>
#include "MS5611.h"
#include "I2Cdev.h"
#include <pressure.h>
//#include "SimpleKalmanFilter.h"
//#include <SPI.h>
#include <SD.h>
//#include <WiFi.h>
//#include <ESPmDNS.h>
//#include <WebServer.h>

// ========== Can Change ========== //
// Change these variables to influence program parameters

// Verbose logging level
// 0 - no logging
// 1 - info logging only
// 2 - debug logging
// 3 - all logging
#define VERBOSE_LEVEL 3
// SD Card logging level
// Same as verbos level but only used for the SD card
#define SD_LEVEL      3

// Sample rates for before and after the
// airbrakes are deployed. Ascent is after launch is
// detected. Descent is after airbrakes are deployed.
// Ascent recommended to be 4, 5, 8, 10, 15, 20, 25, or 33
// Descent recommended to be 1, 2, 4, 5, or 10
// To calculate ascent, take average thrust to weight ratio
// the closest number will be your rate. For example, H160
// on an 11N rocket, would be 160/11 which is ~15 samp/s
#define ASCENT_SAMPLE_RATE    15
#define DESCENT_SAMPLE_RATE   2

// Launch Detection Altitude
// How far the rocket needs to travel upwards before
// a flight is counted as "launched".
// Recommended values between 50-500 feet.
#define LAUNCH_DETECTION      100

// Servo opening and closing values
// These can be from -90 to 90
// NOTE: values may need to be refined
//const int servoOpeningValue = 0;
//const int servoClosingValue = 90;
#define SERVO_OPEN    65
#define SERVO_CLOSE   120

// Servo pin on the board
// Recommended pins are 2, 4, 15-18, 21-23, 25-27, 32-33
//const int servoPin = 15;x
#define SERVO_PIN     9

// Buzzer pin
#define BUZZER_PIN    8

// SD Card Reader CS pin
#define SD_CARD_CS    10

// Servo movment speed
// Values between 0 and 2000
// Get these values from the servo's datasheet
#define MIN_US        500
#define MAX_US        2500

// Now we use altitude activation
// Values are from 0 to infinity measured in meters
uint16_t activationAltitude = 9950;

// Wifi access point for accessing the ESP32 from the ground
// Note: both must be at least 8 characters to work correctly.
const char* ssid = "AggieAir02";
const char* password = "gogojuice";

// MAC Address of the WiFi reciever
// This is used for the avionics data sending
// The MAC address of the black box
//uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x5F, 0x3B, 0xEC};

// ========== Do Not Change ========== //
// Do not change these variables, they are used by the program

Servo servo;

bool servosOpened = false;

//// Webserver variables
//WebServer server(80);
//// Set your Static IP address
//IPAddress local_IP(192, 168, 1, 105);
//// Set your Gateway IP address
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 0, 0);

// SD Card variables
File dataLogFile;

// NOTE: depending on wiring the this may need to be either 0x77 or 0x76
//       see https://forum.arduino.cc/t/need-help-to-connect-ms5611-pressure-sensor-in-i2c-mode/341813
MS5611 ms5611 = MS5611(0x77);
double referencePressure;
// A buffer of measured pressure/temperature while rocket is on the pad
pressure measuredPressures[4];
float measuredTemperatures[4];
// Where are we in the buffer, this increases on each read.
// We also get the current pad pressure via the average of the three not including the last index.
uint8_t measuredPressuresIndex = 0;
uint8_t measuredTemperaturesIndex = 0;
// The average pad pressure/temperature, used for calculating current altitude.
pressure padPressure;
float padTemperature;
// Update the pressures every 5 minutes, keep track with variable
unsigned long previousTime = 0;
// The mode the altimeter is currently in
// - 0 is starting up
// - 1 is on the ground
// - 2 is in flight
// - 3 is deployed
unsigned int flightMode = 0;

// SimpleKalmanFilter(e_mea, e_est, q);
// e_mea: Measurement Uncertainty
// e_est: Estimation Uncertainty
// q: Process Noise
//SimpleKalmanFilter gyroKalmanFilter(1, 1, 1);
//SimpleKalmanFilter accelKalmanFilter(1, 1, .001);

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
