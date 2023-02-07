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
  // Initialize WiFi AP and Web Server
  if (verboseLevel > 0)
    Serial.print("Initializing Web Server...");
//  if (verboseLevel > 0 && WebServer_Setup())
//    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the buzzer
  if (verboseLevel > 0)
    Serial.print("Initializing buzzer...");
  if (verboseLevel > 0 && Buzzer_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the SD card
  // Initialize the Servos
  if (verboseLevel > 0)
    Serial.print("Initializing servos...");
  if (verboseLevel > 0 && Servo_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the Accelerometer
  // Get the initial pressure to calculate relative altitude
  if (verboseLevel > 0)
    Serial.print("Gathering initial pressure...");
  if (verboseLevel > 0 && Barometric_Sensor_Startup())
    Serial.println("DONE!");
  else
    Serial.println("FAILED!");
  // Initialize the WiFi
  // If the verbose level is set to zero, we just preform all setup without checking anything
  if (verboseLevel == 0) {
//    WebServer_Setup();
    Buzzer_Startup();
    Servo_Startup();
    Barometric_Sensor_Startup();
  }
  // Show setup complete.
  if (verboseLevel > 0)
    Serial.println("Setup complete!");
  //  SD_Write("Setup completed");
  // ========== Setup End ========== //
}

void loop() {
  // ========== Loop Start ========== //
  // Check for server connections
//  server.handleClient();
  // Gather data from the barometer for later actions.
  float absolutePressure = Barometric_Sensor_Current_Abs();
  int altitude = 860; //TODO: fix
  if (verboseLevel > 2) {
    Serial.print("Absolute Pressure: ");
    Serial.println(String(absolutePressure));
    Serial.print("Altitude: ");
    Serial.println(String(altitude));
  }
  if (altitude >= activationAltitude) {
    Open_Servos();
  }
  // Test for the rocket being turned, then close the servos if tilted.
  // Log data on the SD card
  // ========== Loop End ========== //
}
