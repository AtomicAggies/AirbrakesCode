// Servo_Funcitons
// by Preston Hager

bool Servo_Startup() {
  // Attach servo to the correct pin
  servo.attach(SERVO_PIN, minUS, maxUS);

  // Show that they open and close
  servo.write(SERVO_CLOSE);
  delay(500);

  servo.write(SERVO_OPEN);
  delay(750);
  servo.write(SERVO_CLOSE);

  return true;
}

// Open the servos based on which servos are selected
void Open_Servos() {
  // Write the opening value to servos
  servo.write(SERVO_OPEN);
  servosOpened = true;
  // Send data to the avionics board over WiFi
//  esp_now_send(broadcastAddress, (uint8_t *) &servosOpened, sizeof(servosOpened));
}

// Closes the servos based on which are selected
// See the notes above for the values.
void Close_Servos() {
  // Write the closing value to servos
  servo.write(SERVO_CLOSE);
  servosOpened = false;
  // Send data to the avionics board over WiFi
//  esp_now_send(broadcastAddress, (uint8_t *) &servosOpened, sizeof(servosOpened));
}

void Disable_Servos() {
  // Detach servos
  servo.detach();
}
