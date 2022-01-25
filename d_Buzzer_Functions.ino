// Buzzer_Functions
// by Preston Hager

bool Buzzer_Startup() {
  // Set the buzzer pin to output
  pinMode(buzzerPin, OUTPUT);

  // Test the buzzer
  tone(buzzerPin, 440.00);
  delay(300);
  noTone(buzzerPin);
  
  return true;
}

void Buzzer_Alert(float freq, int delayTime=300) {
  tone(buzzerPin, freq);
  delay(delayTime);
  noTone(buzzerPin);
}
