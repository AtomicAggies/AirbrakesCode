// Accelerometer_Functions
// by Preston Hager

bool Accelerometer_Startup() {
  // If the IC2 arduino doesn't have fast wire, start it ourselves
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  // Initialize the accelerometer using it's method
  accelgyro.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
  // Calibrate the gyro, this may need to be moved to main loop too
  accelgyro.calibrateGyro();

  return true;
}
