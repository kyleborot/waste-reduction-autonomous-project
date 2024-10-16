#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

float prevTime = 0;
float currentAngleZ = 0; // To store the cumulative rotation (yaw)
float servoZ = 90;  // Starting position for the servo motor (assuming 90 is straight ahead)

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing BNO055...");

  if (!bno.begin()) {
    Serial.println("BNO055 not detected, check wiring.");
    while (1);
  }
  
  delay(1000);
  bno.setExtCrystalUse(true);
  prevTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - prevTime) / 1000.0;  // Time difference in seconds
  prevTime = currentTime;
  
  // Get gyroscope data (angular velocity in deg/s)
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  float gyroZ = gyro.z(); // Angular velocity around Z-axis (yaw)

  // Integrate angular velocity to get total rotation angle
  currentAngleZ += gyroZ * deltaTime;

  // Translate to motor control: assuming we map the angle to the servo
  // You can map this angle to your servo's range (0° to 180°)
  servoZ = 90 + currentAngleZ;  // This is just an example, adjust based on your setup

  // Bound servoZ to servo motor limits (0° to 180°)
  if (servoZ > 180) servoZ = 180;
  if (servoZ < 0) servoZ = 0;

  // Print out the angle for plotting/servo control

  Serial.print(" deg/s, Servo Z: ");
  Serial.println(servoZ);
  
  delay(100);  // Adjust based on the desired response rate
}
