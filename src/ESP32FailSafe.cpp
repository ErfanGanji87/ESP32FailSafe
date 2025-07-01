#include "ESP32FailSafe.h"

// Constructor: set default values
ESP32FailSafe::ESP32FailSafe() {
    timeout = 3000;         // Default loop timeout
    lastFeed = 0;           // No feed yet
    safeMode = false;       // Start in normal mode
    reason = FAILSAFE_NONE; // No failure initially
}

// Initialize system with loop timeout
void ESP32FailSafe::begin(unsigned long loopTimeoutMs) {
    timeout = loopTimeoutMs;
    lastFeed = millis(); // Store current time as the starting point
}

// Must be called regularly in loop() to confirm program is alive
void ESP32FailSafe::feed() {
    if (safeMode) return; // If already in safe mode, skip checks

    // Check if loop has taken too long
    if (millis() - lastFeed > timeout) {
        enterSafeMode(FAILSAFE_LOOP_TIMEOUT, "Loop timeout detected.");
        return;
    }

    // Run all registered health checks
    for (auto& check : checkFunctions) {
        if (!check.func()) {
            String msg = "Check failed: " + check.name;
            enterSafeMode(FAILSAFE_CRITICAL_ERROR, msg.c_str());
            return;
        }
    }

    // All checks passed, update last feed time
    lastFeed = millis();
}

// Add a new check function to monitor something (e.g. sensor, logic)
void ESP32FailSafe::registerCheck(String name, std::function<bool()> checkFunc) {
    checkFunctions.push_back({ name, checkFunc });
}

// Manually mark a fatal system failure and trigger safe mode
void ESP32FailSafe::markCriticalError(String msg) {
    enterSafeMode(FAILSAFE_CRITICAL_ERROR, msg.c_str());
}

// User manually forces safe mode (e.g., via button or network)
void ESP32FailSafe::enterManualSafeMode() {
    enterSafeMode(FAILSAFE_MANUAL, "Manually triggered safe mode.");
}

// Return true if we're currently in safe mode
bool ESP32FailSafe::inSafeMode() {
    return safeMode;
}

// Helper to activate safe mode, set reason, and log message
void ESP32FailSafe::enterSafeMode(FailSafeReason r, const char* msg) {
    safeMode = true;
    reason = r;

    Serial.println("\n============================");
    Serial.println("⚠️ FAILSAFE MODE ACTIVATED ⚠️");
    Serial.print("Reason: ");
    Serial.println(msg);
    Serial.println("============================\n");
}

// Return text description of last failure reason
String ESP32FailSafe::getLastResetReason() {
    switch (reason) {
    case FAILSAFE_NONE: return "No fail";
    case FAILSAFE_LOOP_TIMEOUT: return "Loop timeout";
    case FAILSAFE_CRITICAL_ERROR: return "Critical error";
    case FAILSAFE_MANUAL: return "Manual trigger";
    default: return "Unknown";
    }
}
