// NOTES
// The following are some notes on this sketch's code.

/* ================================
 * Update: 1 October 2021
 * 
 * Needed modules:
 *  - ESP32
 *  - MPU6050 (includes I2Cdev)
 * 
 * ================================
 */
 
/* ================================
 * Update: 13 October 2021
 * 
 * All modules should be included
 * in header files in the project.
 * 
 * ================================
 */

/* ================================
 * Update: 23 January 2022
 * 
 * You should put the following URL
 * in your File > Preferences >
 * Board Manager URLs.
https://dl.espressif.com/dl/package_esp32_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json
 * 
 * Then download the Heltec ESP32
 * boards and libraries through the
 * board and library managers
 * 
 * ================================
 */

/* ================================
 *  Update: 25 January 2023
 *  
 *  Rewriting the code to act like
 *  an altimeter. We now read while
 *  on the pad to create a buffer
 *  of pressures and temperatures.
 *  It then detects when the rocket
 *  launches to start the main
 *  loop and watch for when to deploy.
 */
