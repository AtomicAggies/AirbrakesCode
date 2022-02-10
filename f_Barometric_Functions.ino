// Altimeter_Functions
// by Preston Hager

bool Barometric_Sensor_Startup() {
  // Try to setup the altimeter.
  bool successfulSetup = false;
  for (int i=0; i<10; i++) {
    if (ms5611.begin())
      break;
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
    // If the sensor did setup, return false
    return false;
  }

  // Get a reference pressure for relative altitude readings.
  ms5611.read();
  referencePressure = ms5611.getPressure();
  if (verboseLevel > 0) {
    Serial.print("Current pressure (used for reference): ");
    Serial.println(referencePressure);
  }

  return true;
}

float Barometric_Sensor_Current_Abs() {
  int status = ms5611.read();
  Serial.print(MS5611_READ_OK);
  Serial.print(" == ");
  Serial.println(status);
  Serial.print("Last read: ");
  Serial.println(ms5611.lastRead());
  return ms5611.getPressure();
}
