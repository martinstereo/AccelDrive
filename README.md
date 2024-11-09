# AccelDrive

This project consists of two main components: a server that reads accelerometer data from an MPU6050 sensor and a client that controls a robot car based on the received gestures. The server broadcasts the detected gestures via UDP, and the client receives these gestures to control the robot car's movements.

## Components

### Server (server_accelerometer.ino)

The server reads data from an MPU6050 accelerometer and gyroscope sensor to detect gestures. It then broadcasts these gestures over a UDP connection.

#### Features:
- Connects to a Wi-Fi network.
- Reads accelerometer data to detect gestures.
- Broadcasts detected gestures via UDP.

#### Setup:
1. Connect the MPU6050 sensor to the microcontroller.
2. Update the `arduino_secrets.h` file with your Wi-Fi credentials.
3. Upload the `server_accelerometer.ino` sketch to your microcontroller.

#### Gesture Detection:
- Forward: `F`
- Backward: `B`
- Left: `L`
- Right: `R`
- None: `N`

### Client (client_robot_car.ino)

The client receives the gestures broadcasted by the server and controls the robot car's motors accordingly.

#### Features:
- Connects to a Wi-Fi network.
- Listens for UDP packets containing gesture data.
- Controls the robot car's motors based on the received gestures.

#### Setup:
1. Connect the motor driver to the microcontroller and the robot car's motors.
2. Update the `arduino_secrets.h` file with your Wi-Fi credentials.
3. Upload the `client_robot_car.ino` sketch to your microcontroller.

#### Motor Control:
- Move Forward: `F`
- Move Backward: `B`
- Turn Left: `L`
- Turn Right: `R`
- Stop: `N`

## Wiring Diagrams

### Server (MPU6050 to Microcontroller)
- VCC to 3.3V
- GND to GND
- SCL to SCL
- SDA to SDA

### Client (Motor Driver to Microcontroller)
- ENA to Pin 9
- IN1 to Pin 8
- IN2 to Pin 7
- ENB to Pin 3
- IN3 to Pin 5
- IN4 to Pin 4

## Dependencies

- Adafruit MPU6050 Library
- Adafruit Sensor Library
- WiFiS3 Library
- WiFiUdp Library

## Usage

1. Power on both the server and client microcontrollers.
2. Ensure both devices are connected to the same Wi-Fi network.
3. The server will start broadcasting gestures detected by the MPU6050 sensor.
4. The client will receive these gestures and control the robot car's motors accordingly.

## Troubleshooting

- Ensure the Wi-Fi credentials in `arduino_secrets.h` are correct.
- Verify the wiring connections for both the MPU6050 sensor and the motor driver.
- Check the serial monitor for any error messages or debug information.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
