#include <ESP32FailSafe.h>

// Create an instance of the class
ESP32FailSafe failsafe;

void setup() {
  Serial.begin(115200);

  // Start the failsafe system with 4 second timeout
  failsafe.begin(4000); // Feed must be called at least every 4 seconds

  // Register a health check (e.g. fake sensor check)
  failsafe.registerCheck("SensorCheck", []() {
    int val = analogRead(34);   // Read sensor from pin 34
    return val > 100;           // OK if value is above 100
  });

  pinMode(2, OUTPUT); // Example output (e.g. LED or relay)
}

void loop() {
  // Check if the system is in safe mode
  if (failsafe.inSafeMode()) {
    Serial.println("⚠️ System is in SAFE MODE!");
    digitalWrite(2, LOW);  // Turn off output for safety
    delay(2000);
    return;
  }

  // Normal system operation
  Serial.println("✅ Running normally...");

  digitalWrite(2, HIGH);   // Set output ON

  failsafe.feed();         // Confirm system is alive

  delay(1000);             // Simulate work being done
}
