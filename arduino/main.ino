#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  // Initialize serial communication with the Raspberry Pi
  Serial.begin(9600);

  if(!bno.begin()) {
    Serial.print("BNO055 not detected, check your wiring or I2C address.");
    while (1);
  }
  bno.setMode(Adafruit_BNO055::OPERATION_MODE_NDOF);
  delay(1000);

  prevTime = millis(); //initial time
}

void loop() {
  // Check if data is available from the Raspberry Pi
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    // If the command is 'GET_DATA', send the sensor data
    if (command == "GET_DATA") {
      unsigned long currentTime = millis();
      float deltaTime = (currentTime - prevTime) / 1000.0; // Convert ms to seconds
      prevTime = currentTime;

      // Get linear acceleration (x, y, z) from the sensor in m/s^2
      imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
      float accelX = accel.x();
      float accelY = accel.y();
      float accelZ = accel.z();

      // Calculate new velocity using previous velocity and acceleration
      float velocityX = prevVelocityX + accelX * deltaTime;
      float velocityY = prevVelocityY + accelY * deltaTime;
      float velocityZ = prevVelocityZ + accelZ * deltaTime;

      // Calculate new position using the velocity
      posX += velocityX * deltaTime;
      posY += velocityY * deltaTime;
      posZ += velocityZ * deltaTime;

      // Update previous velocities for the next iteration
      prevVelocityX = velocityX;
      prevVelocityY = velocityY;
      prevVelocityZ = velocityZ;

      // Send position data to the server
      sendCoordinatesToServer(posX, posY, posZ);

    }
  }

  delay(100); // Delay to avoid spamming the serial port
}

void sendCoordinatesToServer(float x, float y, float z) {
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.print(",");
}
