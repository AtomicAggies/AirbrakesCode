// SD_Functions
// by Preston Hager

/*

bool SD_Startup() {
  // Setup the SD SPI class
  pinMode(SD_CS, OUTPUT);
  SPIClass sd_spi(HSPI);
  sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, sd_spi))
    return false;
  return true;
}

void SD_Write(char dataString[]) {

  if(!SD_Init){
    // Setup the SD SPI class
    pinMode(SD_CS, OUTPUT);
    SPIClass sd_spi(HSPI);
    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, sd_spi)) {
      Serial.println("SD init failed");
    } else {
      Serial.println("SD Initialized");
      SD_Init = true;
    }
  }

  // Calculate the current time since start
  unsigned long nowMillis = millis();
  unsigned long seconds = nowMillis % 1000;
  unsigned long miliseconds = nowMillis - (seconds * 1000);
  unsigned long minutes = seconds % 60;
  unsigned long hours = minutes % 60;
  // Convert numbers into a string
  String timeStringString = "[ " + String(hours) + ":" + String(minutes) + ":" + String(seconds) + ":" + String(miliseconds) + " ]";
  char timeString[timeStringString.length()];
  timeStringString.toCharArray(timeString, timeStringString.length());
  // Create the data file variable
  File dataFile = SD.open("/datalog.txt", FILE_WRITE);
  Serial.println(dataFile);
  if (dataFile) {
    // Print the time stamp to the file
    unsigned int c = 0;
//    while (timeString[c] != 0) {
//      dataFile.write(timeString[c]);
//      c += 1;
//    }
//    dataFile.write(hours);
//    dataFile.write(":");
//    dataFile.write(String(minutes));
//    dataFile.write(":");
//    dataFile.write(String(seconds));
//    dataFile.write(":");
//    dataFile.write(String(miliseconds));
//    dataFile.write(" ] ");
    // Then print the data
    c = 0;
    while (dataString[c] != 0) {
      dataFile.write(dataString[c]);
      c += 1;
    }
    Serial.print("Logged data to file: ");
    Serial.println(dataString);
  } else {
    Serial.println("Failed to open file");
  }
  
  Serial.println("here");
  // And close the file
  dataFile.close();
  
  Serial.println("here2");
}

*/
