// SD_Functions
// by Preston Hager

bool SD_Startup() {
  // SD.begin(uint8_t ssPin=SS, SPIClass &spi=SPI, uint32_t frequency=4000000, const char * mountpoint="/sd", uint8_t max_files=5, bool format_if_empty=false);
  if (!SD.begin(SDChipSelect, SPI, 4000000, "/sd", 1, true))
    return false;
  return true;
}

void SD_Write(String dataString) {
  // Calculate the current time since start
  unsigned long nowMillis = millis();
  unsigned long seconds = nowMillis % 1000;
  unsigned long miliseconds = nowMillis - (seconds * 1000);
  unsigned long minutes = seconds % 60;
  unsigned long hours = minutes % 60;
  // Create the data file variable
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    // Print the time stamp to the file
    dataFile.print("[ ");
    dataFile.print(String(hours));
    dataFile.print(":");
    dataFile.print(String(minutes));
    dataFile.print(":");
    dataFile.print(String(seconds));
    dataFile.print(":");
    dataFile.print(String(miliseconds));
    dataFile.print(" ] ");
    // Then print the data
    dataFile.println(dataString);
    // And close the file
    dataFile.close();
    Serial.println("Logged on SD card");
  } else {
    Serial.println("File open problem on SD card");
  }
}
