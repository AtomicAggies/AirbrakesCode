// SD_Funcitons

bool SD_Setup() {
  if(!SD.begin(SD_CARD_CS)) {
    return false;
  }
  // Ensure we overwrite the previous file
  SD.remove("data_log.csv");
  dataLogFile = SD.open("data_log.csv", FILE_WRITE);
  // Write the headers to the file
  dataLogFile.println("Time,Flight Mode,Pressure,Altitude");
  dataLogFile.flush();
  return true;
}
