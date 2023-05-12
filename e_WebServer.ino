//// Web Server Functions
//
//bool WebServer_Setup() {
//  WiFi.softAP(ssid, password);
//  WiFi.softAPConfig(local_IP, gateway, subnet);
//  // Server path definitions
//  server.on("/", handle_index);
//  server.onNotFound(handle_NotFound);
//  server.begin();
//  return true;
//}
//
//void handle_index() {
//  if(server.hasArg("activationAltitude")) {
//    activationAltitude = (uint16_t) server.arg("activationAltitude").toInt();
//    Serial.println("Activation altitude updated to: " + String(activationAltitude));
//  }
//  if (server.hasArg("testServo")) {
//    uint8_t testServos = (uint16_t) server.arg("testServo").toInt();
//    if (testServos > 0) {
//      Serial.print("Testing servos...");
//      Servo_Test();
//      Serial.println("DONE!");
//    }
//  }
//  server.send(200, "text/html", GenHTML()); 
//}
//
//void handle_NotFound(){
//  server.send(404, "text/plain", "Not found");
//}
//
//String GenHTML(){
//  String ptr = "<!DOCTYPE html> <html>\n";
//  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
//  ptr +="<title>Aggie Air Control</title>\n";
//  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
//  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
//  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
//  ptr +="</style>\n";
//  ptr +="</head>\n";
//  ptr +="<body>\n";
//  ptr +="<h1>Atomic Aggies</h1>\n";
//  ptr +="<h3>Airbrakes System Settings</h3>\n";
//  // Here is where the main body should go!
//  ptr +="<p>Flight mode: ";
//  ptr +=String(flightMode);
//  ptr +="</p>\n";
//  ptr +="<form method=\"POST\" action=\"/\">\n";
//  ptr +="<p>Activation Altitude (feet): <input type=\"int\" name=\"activationAltitude\" value=\"" + String(activationAltitude) + "\"></p>\n";
//  ptr +="<input type=\"checkbox\" name=\"testServo\" value=\"1\">\n";
//  ptr +="<label for=\"testServo\">Test Servos?</label><br>\n";
//  ptr +="<input type=\"submit\" value=\"Update\">\n";
//  ptr +="</form>\n";
//  ptr +="</body>\n";
//  ptr +="</html>\n";
//  return ptr;
//}
