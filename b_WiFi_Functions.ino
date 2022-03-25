// WiFi_Funcitons
// by Preston Hager

/*

bool WiFi_Startup() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    return false;
  }
  // Coppy MAC address
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer to ESP NOW
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    return false;
  }
  return true;
}

*/
