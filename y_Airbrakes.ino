// Airbrakes ESP32
// by Preston Hager

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // ========== Setup Begin ========== //
  Serial.begin(115200);
  // Wait for serial connection to complete.
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  delay(250);
  if (verboseLevel > 0)
    Serial.println("Program started. Setup starting.");
  // Start the Heltec board
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/, false /*PABOOST Enable*/, 470E6 /*Frequency*/);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Phase: Program setup");
  Heltec.display->display();
  // Allocate all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  // Initialize the buzzer
  if (verboseLevel > 0)
    Serial.print("Initializing buzzer...");
  if (verboseLevel > 0 && Buzzer_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the SD card
  if (verboseLevel > 0)
    Serial.print("Intializing SD card...");
  if (verboseLevel > 0 && SD_Startup())
    Serial.println("DONE!");
  /*
  else {
    Serial.println("FAILED!");
    // Display the failure and sound the buzzer
    Heltec.display->drawString(0, 12, "FAILED: No SD card");
    Heltec.display->display();
    while(1) {
      Buzzer_Alert(329.63, 200);
      delay(200);
    }
  }
  */
  // Initialize the Servos
  if (verboseLevel > 0)
    Serial.print("Initializing servos...");
  if (verboseLevel > 0 && Servo_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the Accelerometer
  if (verboseLevel > 0)
    Serial.print("Initializing Accelerometer...");
  if (verboseLevel > 0 && Accelerometer_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Get the initial pressure to calculate relative altitude
  if (verboseLevel > 0)
    Serial.print("Gathering initial pressure...");
  if (verboseLevel > 0 && Barometric_Sensor_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the WiFi
  if (verboseLevel > 0)
    Serial.print("Setting up WiFi and ESP NOW...");
  if (verboseLevel > 0 && WiFi_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Show setup complete.
  if (verboseLevel > 0)
    Serial.println("Setup complete!");
  SD_Write("Setup completed");
  // Write the next step to the display
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Phase: Program loop");
  Heltec.display->drawString(0, 12, "Flaps: Closed");
  Heltec.display->display();
  // ========== Setup End ========== //
}

void loop() {
  // ========== Loop Start ========== //
  // Gather accelerometer data
  float estimated_yaccel;
  if (activationType & 0b00000010) {
    accelgyro.getAcceleration(&ax, &ay, &az);
    estimated_yaccel = accelKalmanFilter.updateEstimate((float) ay);
    if (verboseLevel > 2) {
      Serial.print("Estimated accel: ");
      Serial.println(String(estimated_yaccel));
    }
  }
  // Analyze the gyroscope for later actions.
  accelgyro.getRotation(&gx, &gy, &gz);
  float estimated_gyrox = gyroKalmanFilter.updateEstimate((float) gx);
  float estimated_gyroy = gyroKalmanFilter.updateEstimate((float) gy);
  float estimated_gyroz = gyroKalmanFilter.updateEstimate((float) gz);
  if (verboseLevel > 2) {
    Serial.print("Estimated gyro: ");
    Serial.print(String(estimated_gyrox));
    Serial.print(", ");
    Serial.print(String(estimated_gyroy));
    Serial.print(", ");
    Serial.println(String(estimated_gyroz));
  }
  if (verboseLevel > 1) {
    Serial.print("Gyro: ");
    Serial.print(String(estimated_gyrox - uprightX));
    Serial.print(", ");
    Serial.println(String(estimated_gyroz - uprightZ));
  }
  // Gather data from the altimeter for later actions.
  float absolutePressure;
  if (activationType & 0b00000001) {
    // Update the MS5611 reading then find the altitudes
//    ms5611.read();
    absolutePressure = Barometric_Sensor_Current_Abs();
    if (verboseLevel > 2) {
      Serial.print("Absolute Pressure: ");
      Serial.println(String(absolutePressure));
    }
  }
  // Test for the rocket being turned, then close the servos if tilted.
  if (!(estimated_gyrox >= uprightX - 40 && estimated_gyrox <= uprightX + 40) || !(estimated_gyroz >= uprightZ - 40 && estimated_gyroz <= uprightZ + 40)) {
      Close_Servos();
      SD_Write("Closed servos");
  } else if (!servosOpened) {
    // Test if we reached the preset altitude
    if ((activationType & 0b00000001)) {
      Open_Servos();
      SD_Write("Opened servos");
    }
    // Test if we have the G Force Required to activate airbrakes
    if ((activationType & 0b00000010) && estimated_yaccel >= GForceActivation) {
        // Open the servos since we are within tilt range.
        Open_Servos();
        SD_Write("Opened servos");
    }
  }
  // Log data on the SD card
  String dataStringString = "Gyro: " + String(estimated_gyrox - uprightX) + ", " + String(estimated_gyroz - uprightZ) + "; Absolute Pressure: " + String(absolutePressure);
  char dataString[dataStringString.length()];
  dataStringString.toCharArray(dataString, dataStringString.length());
  SD_Write(dataString);
  // ========== Loop End ========== //
}
