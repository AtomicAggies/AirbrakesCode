//shared libries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
//accelerometer libraries
#include <Adafruit_FXAS21002C.h>
#include <Wire.h>
//pressure libraries
#include "Adafruit_BMP3XX.h"


//define pressure pins
#define BMP_SCK 41
#define BMP_MISO 14
#define BMP_MOSI 15
#define BMP_CS 16
//define pressure values
#define SEALEVELPRESSURE_HPA (1013.25)

File SD_File;

//accelerometer
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
//pressure
Adafruit_BMP3XX bmp;


bool startNano = false; // Flag to start Nano

//accelerometer function
void displaySensorDetails() {
  sensor_t sensor;
  gyro.getSensor(&sensor);
  // re-open the file for writing:
  SD_File = SD.open("launch_log.txt", FILE_WRITE);
  SD_File.println("------------------------------------");
  SD_File.print("Sensor:       ");
  SD_File.println(sensor.name);
  SD_File.print("Driver Ver:   ");
  SD_File.println(sensor.version);
  SD_File.print("Unique ID:    0x");
  SD_File.println(sensor.sensor_id, HEX);
  SD_File.print("Max Value:    ");
  SD_File.print(sensor.max_value);
  SD_File.println(" rad/s");
  SD_File.print("Min Value:    ");
  SD_File.print(sensor.min_value);
  SD_File.println(" rad/s");
  SD_File.print("Resolution:   ");
  SD_File.print(sensor.resolution);
  SD_File.println(" rad/s");
  SD_File.println("------------------------------------");
  SD_File.println("");
  // close the file:
  SD_File.close();
  delay(500);
}

void setup() {
//start sd card
SD.begin(BUILTIN_SDCARD);

pinMode(35,OUTPUT);
digitalWrite(35, LOW);

  //accelerometer setup
  // open the accelerometer file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  SD_File = SD.open("launch_log.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (SD_File) {
    SD_File.println("Power ON Complete");
    SD_File.println("Starting Accelerometer Recording");
    // close the file:
    SD_File.close();
    // Initialise the accelerometer 
    if (!gyro.begin()) {
      // re-open the file for writing:
      SD_File = SD.open("launch_log.txt", FILE_WRITE);
      // There was a problem detecting the FXAS21002C ... check your connections
      SD_File.println("Ooops, no FXAS21002C detected ... Check your wiring!");
      // close the file:
      SD_File.close();
      while (1);
    }
    displaySensorDetails();
  }

  //pressure setup
  //if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    SD_File = SD.open("launch_log.txt", FILE_WRITE);
    SD_File.println("Could not find a valid BMP3 sensor, check wiring!");
    SD_File.close();
    while (1);
  }  
    // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // Setup data.csv headers
  SD_File = SD.open("data.csv", FILE_WRITE);
  SD_File.println("Time (ms),\tAccel_X,\tAccel_Y,\tAccel_Z,\tMag (rad/s),\tPressure (hPa),\tTemperature (C),\tAltitude (m)");
  SD_File.close();
}

void loop() {
  //accelerometer
  // Get a new accelerometer event 
  sensors_event_t event;
  gyro.getEvent(&event);
  // re-open the accelerometer file for writing:
  
  double mag = sqrt(event.gyro.x*event.gyro.x + event.gyro.y*event.gyro.y + event.gyro.z*event.gyro.z);
  SD_File = SD.open("data.csv", FILE_WRITE);
  SD_File.print(millis());
  // Display the results (speed is measured in rad/s) 
  SD_File.print(event.gyro.x);
  SD_File.print(",\t");
  SD_File.print(event.gyro.y);
  SD_File.print(",\t");
  SD_File.print(event.gyro.z);
  SD_File.print(",\t");
  SD_File.print(mag);
  // close the file:
  SD_File.close();

  // Check the condition to start Nano
  if (!startNano) {
      if (mag >= 1) {
        digitalWrite(35, HIGH);
        startNano = true;
      }
    }
    
  delay(100);

  //pressure
  if (! bmp.performReading()) {
    SD_File = SD.open("launch_log.txt", FILE_WRITE);
    SD_File.println("Failed to perform reading :(");
    SD_File.close();
    // Log an empty data entry
    SD_File.print(",\tNaN,\tNaN,\tNaN");
    return;
  }
  //open pressure file
  SD_File = SD.open("data.csv", FILE_WRITE);
  //pressure reading
  SD_File.print(",\t");
  SD_File.print(bmp.pressure / 100.0);
  //temp reading
  SD_File.print(",\t");
  SD_File.print(bmp.temperature);
  //altitude reading
  SD_File.print(",\t");
  SD_File.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  //adds a gap between reading values
  SD_File.println();
  SD_File.close();
  delay(100);
}
