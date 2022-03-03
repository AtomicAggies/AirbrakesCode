// Servo_Funcitons
// by Preston Hager

bool Servo_Startup() {
  // Set servos to operate at 50Hz (standard)
  servo.setPeriodHertz(50);

  // Attach servos to the correct pin
  servo.attach(SERVO_PIN, minUS, maxUS);
  pwm.attachPin(27, 10000);

  // Show that they open and close
  servo.write(SERVO_CLOSE);

  servo.write(SERVO_OPEN);
  delay(300);
  servo.write(SERVO_CLOSE);

  return true;
}

// Open the servos based on which servos are selected
void Open_Servos() {
  // Write the opening value to servos
  servo.write(SERVO_OPEN);
  servosOpened = true;
  // Send data to the avionics board over WiFi
  esp_now_send(broadcastAddress, (uint8_t *) &servosOpened, sizeof(servosOpened));
}

// Closes the servos based on which are selected
// See the notes above for the values.
void Close_Servos() {
  // Write the closing value to servos
  servo.write(SERVO_CLOSE);
  servosOpened = false;
  // Send data to the avionics board over WiFi
  esp_now_send(broadcastAddress, (uint8_t *) &servosOpened, sizeof(servosOpened));
}

void Disable_Servos() {
  // Detach servos
  servo.detach();
  pwm.detachPin(27);
}
