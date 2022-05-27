// Web Server Functions
// by Preston Hager

bool WebServer_Setup() {
  WiFi.softAP(ssid, password);
  if (!MDNS.begin("esp32")) {
    Serial.println("Error starting mDNS.");
    return false;
  }
  // Server path definitions
  server.on("/", handle_index);
  server.onNotFound(handle_NotFound);
  server.begin();
  return true;
}

void handle_index() {
  Serial.println("Connect");
  if(server.hasArg("seaLevelPressure")) {
    currentSeaLevel = server.arg("seaLevelPressure").toFloat();
    Serial.println("Sea level pressure updated to: " + String(currentSeaLevel));
  }
  if(server.hasArg("activationAltitude")) {
    activationAltitude = server.arg("activationAltitude").toInt();
    Serial.println("Activation altitude updated to: " + String(activationAltitude));
  }
  server.send(200, "text/html", SendHTML(currentSeaLevel)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float currentSeaLevelValue){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Atomic Aggies</h1>\n";
  ptr +="<h3>Airbrakes System Settings</h3>\n";
  // Here is where the main body should go!
  ptr +="<form method=\"POST\" action=\"/\">\n";
  ptr +="<p>Sea Level Pressure: <input type=\"float\" name=\"seaLevelPressure\" value=\"" + String(currentSeaLevelValue) + "\"></p>\n";
  ptr +="<p>Activation Altitude: <input type=\"int\" name=\"activationAltitude\" value=\"" + String(activationAltitude) + "\"></p>\n";
  ptr +="<input type=\"submit\" value=\"Update\">\n";
  ptr +="</form>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
