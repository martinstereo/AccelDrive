#include <WiFiS3.h>
#include <WiFiUdp.h>
#include "arduino_secrets.h"

// Motor control pins
#define ENA 11
#define IN1 7
#define IN2 8
#define ENB 5
#define IN3 9
#define IN4 10

// Wi-Fi credentials
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// UDP settings
unsigned int localPort = 4210;  // Local port to listen on
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);

  // Setup motor pins as OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start UDP
  Udp.begin(localPort);
  Serial.println("UDP client started");
}

void loop() {
  // Check for incoming UDP packets
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.print("Received packet: ");
    Serial.println(incomingPacket);

    // Control motors based on the received gesture
    char gesture = incomingPacket[0];
    switch (gesture) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'N':
      default:
        stopMotors();
        break;
    }
  }

  // Small delay before the next loop
  delay(50);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnRight() {
  digitalWrite(IN1, LOW);  // Right motor forward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);   // Left motor stop
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 0);      // Stop left motor
}

void turnLeft() {
  digitalWrite(IN1, LOW);   // Right motor stop
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Left motor forward
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 0);      // Stop right motor
  analogWrite(ENB, 255);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
