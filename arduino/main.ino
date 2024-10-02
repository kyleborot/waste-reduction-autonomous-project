// Define your sensor pin
const int sensorPin = A0; // Example: Analog pin for a temperature sensor

void setup() {
  // Initialize serial communication with the Raspberry Pi
  Serial.begin(9600);

  // Setup the sensor pin as input
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Check if data is available from the Raspberry Pi
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    // If the command is 'GET_DATA', send the sensor data
    if (command == "GET_DATA") {
      int sensorValue = analogRead(sensorPin); // Read sensor value
      Serial.println(sensorValue);             // Send the value back
    }
  }

  delay(100); // Delay to avoid spamming the serial port
}
