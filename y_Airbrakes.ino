// Airbrakes ESP32
// by Preston Hager

void setup() {
  // ========== Setup Begin ========== //
  if (verboseLevel > 0) {
    Serial.begin(115200);
    // Wait for serial connection to complete.
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
    delay(250);
    Serial.println("Program started. Setup starting.");
    Serial.print("Initializing Web Server...");
    if (WebServer_Setup()) {
      Serial.println("DONE!");
    } else {
      Serial.println("FAILED!");
    }
    Serial.print("Initializing buzzer...");
    if (Buzzer_Startup()) {
      Serial.println("DONE!");
    } else {
      Serial.println("FAILED!");
    }
    Serial.print("Initializing servos...");
    if (Servo_Startup()) {
      Serial.println("DONE!");
    } else {
      Serial.println("FAILED!");
    }
    Serial.print("Gathering initial pressure...");
    if (Barometric_Sensor_Startup()) {
      Serial.println("DONE!");
    } else {
      Serial.println("FAILED!");
    }
    Serial.println("Setup complete!");
  } else {
    WebServer_Setup();
    Buzzer_Startup();
    Servo_Startup();
    Barometric_Sensor_Startup();
  }
  flightMode = 1;
  // ========== Setup End ========== //
}

void loop() {
  // ========== Loop Start ========== //
  if (flightMode == 1) {
    // Update pad pressures every 5 minutes
    if (millis() - previousTime >= 5*60*1000) {
      Barometric_Sensor_Read();
      previousTime = millis();
      Serial.print("Updated pad pressure. Measured at: ");
      float measuredPressure = measuredPressures[measuredPressuresIndex].getMilliBar();
      Serial.println(measuredPressure);
    }
    // Look for a launch
    // currentPressure is measured in millibars
    float currentPressure = Barometric_Sensor_Current_Abs();
    // If the current pressure is significatly lower than the pad pressure,
    // then the rocket is flying!
    if (padPressure.getMilliBar() > (currentPressure + SENSITIVITY)) {
      #if VERBOSE > 0
        Serial.println("Launch detected!");
      #endif
      flightMode = 2;
    }
    // Handle web connections
    server.handleClient();
    // delay a little to keep the processor cooler
    delay(50);
  } else if (flightMode == 2) {
    // Look for the activation altitude and open the servos
    float altitude = Barometric_Get_Altitude();
    #if VERBOSE > 0
      Serial.print("Altitude: ");
      Serial.println(altitude);
    #endif
    if (altitude >= activationAltitude) {
      Open_Servos();
      #if VERBOSE > 0
        Serial.println("Airbrakes deployed!");
      #endif
      flightMode = 3;
    }
  } else {
    // Fins have been extended
  }
  // ========== Loop End ========== //
}
