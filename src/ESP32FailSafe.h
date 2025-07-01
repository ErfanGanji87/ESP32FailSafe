#ifndef ESP32_FAILSAFE_H
#define ESP32_FAILSAFE_H

#include <Arduino.h>
#include <functional>
#include <vector>

// Enum to represent reasons for entering Safe Mode
enum FailSafeReason {
	FAILSAFE_NONE,             // No failure detected
	FAILSAFE_LOOP_TIMEOUT,     // Main loop timeout (feed not called in time)
	FAILSAFE_CRITICAL_ERROR,   // A critical check failed
	FAILSAFE_MANUAL            // Manually triggered safe mode
};

// Structure to hold each health check function
struct CheckFunction {
	String name;                          // Check name for logging
	std::function<bool()> func;           // The function to call
};

// Main class
class ESP32FailSafe {
private:
	unsigned long timeout;                // Max time allowed between feed() calls
	unsigned long lastFeed;              // Last time feed() was called
	bool safeMode;                        // True if we're in safe mode
	FailSafeReason reason;               // Why we entered safe mode
	std::vector<CheckFunction> checkFunctions; // All registered checks

	// Enter safe mode and optionally log message
	void enterSafeMode(FailSafeReason r, const char* msg = "");

public:
	ESP32FailSafe();

	// Initialize system with optional loop timeout (ms)
	void begin(unsigned long loopTimeoutMs = 3000);

	// Call in every loop() cycle to confirm system is alive
	void feed();

	// Register custom health checks (e.g., sensor readings)
	void registerCheck(String name, std::function<bool()> checkFunc);

	// Manually trigger a critical error
	void markCriticalError(String msg);

	// Manually trigger safe mode
	void enterManualSafeMode();

	// Return true if we are in safe mode
	bool inSafeMode();

	// Return a human-readable reason for safe mode
	String getLastResetReason();
};

#endif
