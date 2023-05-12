// SD_Funcitons

bool SD_Setup() {
  if(!SD.begin(SD_CARD_CS)) {
    return false;
  }
  dataLogFile = SD.open("log.csv", FILE_WRITE);
  return true;
}
