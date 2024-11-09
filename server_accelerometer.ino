#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include "arduino_secrets.h"

// Constants and Buffers for Gesture Detection
#define SERIAL_BAUD_RATE 115200
#define UDP_PORT 4210  // UDP port for communication

// Wi-Fi Setup
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;

// UDP instance
WiFiUDP Udp;
IPAddress broadcastIP(10, 228, 33, 158);  // Updated broadcast address

// Sensor instance
Adafruit_MPU6050 mpu;

// Variable to store current movement as character
char currentMovement = 'N';  // 'N' for none or no detection

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(UDP_PORT);
  Serial.println("UDP server started");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 initialized");
}

void loop() {
  // Read accelerometer data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Determine movement based on accelerometer data
  if (a.acceleration.x > 2) {
    currentMovement = 'F';  // Forward (was Right)
  } else if (a.acceleration.x < -2) {
    currentMovement = 'B';  // Backward (was Left)
  } else if (a.acceleration.y > 2) {
    currentMovement = 'L';  // Left (was Forward)
  } else if (a.acceleration.y < -2) {
    currentMovement = 'R';  // Right (was Backward)
  } else {
    currentMovement = 'N';  // None
  }

  // Broadcast the current movement via UDP
  Udp.beginPacket(broadcastIP, UDP_PORT);
  Udp.write(currentMovement);
  int result = Udp.endPacket();
  if (result == 1) {
    Serial.println("Movement broadcasted: " + String(currentMovement));
  } else {
    Serial.println("Failed to send UDP packet, result: " + String(result));
  }

  // Optional delay to prevent overload
  delay(100);
}