// Airbrakes ESP32
// by Preston Hager

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
  // Allocate all timers
//  ESP32PWM::allocateTimer(0);
//  ESP32PWM::allocateTimer(1);
//  ESP32PWM::allocateTimer(2);
//  ESP32PWM::allocateTimer(3);
  // Initialize the buzzer
  if (verboseLevel > 0)
    Serial.print("Initializing buzzer...");
  if (verboseLevel > 0 && Buzzer_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the SD card
  //  if (verboseLevel > 0)
  //    Serial.print("Intializing SD card...");

  //  if (verboseLevel > 0){// && SD_Startup())
  //    pinMode(SD_CS, OUTPUT);
  //    SPIClass sd_spi(HSPI);
  //    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  //    if (!SD.begin(SD_CS, sd_spi))
  //      Serial.println("SD Initialized");
  //    Serial.println("DONE!");
  //  }
  /*
    else {
    Serial.println("FAILED!");
    // Sound the buzzer
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
//  if (verboseLevel > 0)
//    Serial.print("Initializing Accelerometer/Gyroscope...");
//  if (verboseLevel > 0 && Accelerometer_Startup())
//    Serial.println("DONE!");
//  else
//    Serial.println("FAILED!");
  // Get the initial pressure to calculate relative altitude
  if (verboseLevel > 0)
    Serial.print("Gathering initial pressure...");
  if (verboseLevel > 0 && Barometric_Sensor_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the WiFi
//  if (verboseLevel > 0)
//    Serial.print("Setting up WiFi and ESP NOW...");
//  if (verboseLevel > 0 && WiFi_Startup())
//    Serial.println("DONE!");
//  else
//    Serial.println("FAILED!");
  // Show setup complete.
  if (verboseLevel > 0)
    Serial.println("Setup complete!");
  //  SD_Write("Setup completed");
  // ========== Setup End ========== //
}

void loop() {
  // ========== Loop Start ========== //
  // Analyze the gyroscope for later actions.
//  accelgyro.getRotation(&gx, &gy, &gz);
//  Vector normGyro = accelgyro.readNormalizeGyro();
//  float estimated_gyrox = gyroKalmanFilter.updateEstimate((float) normGyro.XAxis);
//  float estimated_gyroy = gyroKalmanFilter.updateEstimate((float) normGyro.YAxis);
//  float estimated_gyroz = gyroKalmanFilter.updateEstimate((float) normGyro.ZAxis);
//  if (verboseLevel > 2) {
//    Serial.print("Estimated gyro: ");
//    Serial.print(String(estimated_gyrox));
//    Serial.print(", ");
//    Serial.print(String(estimated_gyroy));
//    Serial.print(", ");
//    Serial.println(String(estimated_gyroz));
//  }
//  if (verboseLevel > 1) {
//    Serial.print("Gyro: ");
//    Serial.print(String(estimated_gyrox - uprightX));
//    Serial.print(", ");
//    Serial.println(String(estimated_gyroz - uprightZ));
//  }
  // Gather data from the altimeter for later actions.
  float absolutePressure = Barometric_Sensor_Current_Abs();
  if (verboseLevel > 2) {
    Serial.print("Absolute Pressure: ");
    Serial.println(String(absolutePressure));
  }
  // Test for the threshold pressure
  if (absolutePressure <= PRESSURE_ACTIVATION) {
    Open_Servos();
    //    SD_Write("Opened servos");
  } //else {
//    Close_Servos();
//  }
  // Test for the rocket being turned, then close the servos if tilted.
//  if (!(estimated_gyrox >= uprightX - TiltThreshold && estimated_gyrox <= uprightX + TiltThreshold) || !(estimated_gyroz >= uprightZ - TiltThreshold && estimated_gyroz <= uprightZ + TiltThreshold)) {
//    Close_Servos();
    //      SD_Write("Closed servos");
//  }
  // Log data on the SD card
  //  String dataStringString = "Gyro: " + String(estimated_gyrox - uprightX) + ", " + String(estimated_gyroz - uprightZ) + "; Absolute Pressure: " + String(absolutePressure);
  //  char dataString[dataStringString.length()];
  //  dataStringString.toCharArray(dataString, dataStringString.length());
  //  SD_Write(dataString);
  // ========== Loop End ========== //
}
