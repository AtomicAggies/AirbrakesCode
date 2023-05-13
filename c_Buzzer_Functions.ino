// Buzzer_Functions

bool Buzzer_Startup() {
  // Set the buzzer pin to output
  pinMode(BUZZER_PIN, OUTPUT);

  // Test the buzzer
  tone(BUZZER_PIN, 440.00);
  delay(300);
  noTone(BUZZER_PIN);
  
  return true;
}

void Buzzer_Alert(float freq, int delayTime=300) {
  tone(BUZZER_PIN, freq);
  delay(delayTime);
  noTone(BUZZER_PIN);
}
