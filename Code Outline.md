# Airbrakes Code Outline

```
// Airbrakes.ino

Import any libraries neccessary.

#define SD_CS		2
#define SD_SCK		17
#define SD_MOSI	23
#define SD_MISO	13

#define VERBOSE_LEVEL 3

#define SERVO_PIN		15
#define BUZZER_PIN	12

#define PRESSURE_THRESHOLD	160

uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x5F, 0x3B, 0xEC};

Set up other global variables for program:

- Servo
- ESP32PWM
- MPU6050
- esp_now_peer_info_t peerInfo;
- MS5611
- SimpleKalmanFilters

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif

int16_t uprightX, uprightZ;
bool servosOpened = false;
```

```
// WiFi

Use the file already made:
has function WiFi_Startup to start connection then use

esp_now_send(broadcastAddress, (uint8_t *) &servosOpened, sizeof(servosOpened));

to send the value 1|0 to avionics
```