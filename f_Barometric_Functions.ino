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
    if (i == 9)
      return false;
  }

  // Get the average pad pressure for calculations
  for (uint8_t i=0; i<4; i++) {
    Barometric_Sensor_Read();
    delay(100);
  }

  // Set the temperature offset
  ms5611.setTemperatureOffset(273.15);

  return true;
}

void Barometric_Sensor_Read() {
  // Read the current pressure and put it in the buffer
  ms5611.read();
  measuredPressures[measuredIndex].setMilliBar(ms5611.getPressure());
  measuredTemperatures[measuredIndex] = ms5611.getTemperature();
  // Find the average of the recorded pressures, not including the current index.
  float pressureSum = 0.0f;
  float temperatureSum = 0.0f;
  for (uint8_t i=0; i<4; i++) {
    if (i != measuredIndex) { // Skip over the last read value.
      pressureSum += measuredPressures[i].getMilliBar();
      temperatureSum += measuredTemperatures[i];
    }
  }
  padPressure.setMilliBar(pressureSum / 3.0);
  padTemperature = temperatureSum / 3.0;
  // Increase where we are in the buffer for next time.
  measuredPressuresIndex ++;
}

float Barometric_Sensor_Current_Abs() {
  ms5611.read();
  return ms5611.getPressure();
}

float Barometric_Get_Altitude() {
  ms5611.read();
  pressure currentPressure = pressure(ms5611.getPressure());
  return (padTemperature/-0.0065) * (pow((currentPressure.getPascal()/padPressure.getPascal()), ((8.31432*0.0065)/(9.80665* 0.0289644)))-1);
}

//int Pressure_To_Altitude(float pressure) {
//  return -44330.7692308 * (pow((pressure / currentSeaLevel), (0.1902632365)) - 1);
//}
