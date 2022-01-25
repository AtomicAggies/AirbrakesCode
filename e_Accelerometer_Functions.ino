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
  accelgyro.initialize();

  int16_t unused;
  accelgyro.getRotation(&uprightX, &unused, &uprightZ);

  // Test the connection and return the status
  return accelgyro.testConnection();
}
