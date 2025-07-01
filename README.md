# 🛡 ESP32FailSafe

**ESP32FailSafe** is a lightweight yet powerful fail-safe & watchdog system for critical ESP32-based projects.  
It actively monitors your main loop and essential subsystems (like sensors or communication) and automatically switches the device to **Safe Mode** in case of errors, delays, or failures.

---

## 🚨 Why Fail-Safe Matters

When building industrial, smart home, or robotics applications with ESP32, even a small software bug or sensor disconnect can lead to dangerous behaviors like:
- Motors running wild  
- Relays staying ON too long  
- Stuck loops or frozen Wi-Fi communication

This library ensures your system is always **under control** — and **shuts down safely** if it's not.

---

## ✅ Features

- ⏱️ **Loop watchdog:** Detects if the `loop()` is stuck or slow  
- 🧪 **Health checks:** Custom checks for sensors, logic, or connectivity  
- 🛑 **Safe Mode engine:** Executes only minimal code when fault detected  
- 📄 **Error logging:** Provides detailed reason for failure  
- 🧠 **Manual trigger:** Put device into Safe Mode from UI, button, or network  
- 🔄 **Extendable:** Minimal and modular C++ design

---

## 🔧 Installation

1. Copy the `ESP32FailSafe.h` and `ESP32FailSafe.cpp` to your project folder  
2. Or install it via GitHub:


git clone https://github.com/ErfanGanji87/ESP32FailSafe


Then include it in your sketch:

```cpp
#include <ESP32FailSafe.h>
```

---

## 🚀 Quick Start

```cpp
#include <ESP32FailSafe.h>

ESP32FailSafe failsafe;

void setup() {
  Serial.begin(115200);
  failsafe.begin(5000); // 5s timeout for loop

  failsafe.registerCheck("TemperatureSensor", []() {
    return analogRead(34) > 100; // Check your sensor
  });
}

void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("⚠ Safe mode active");
    return;
  }

  // Normal operation
  failsafe.feed();
  delay(1000);
}
```

---

## 🧩 API Reference

### `void begin(unsigned long loopTimeoutMs = 3000);`
Initializes the library.  
- `loopTimeoutMs`: maximum time (in ms) allowed between `feed()` calls.

---

### `void feed();`
Must be called regularly inside `loop()` to avoid watchdog timeout.

---

### `void registerCheck(String name, std::function<bool()> checkFunc);`
Registers a function to validate the health of a component.

```cpp
failsafe.registerCheck("WiFi", []() {
  return WiFi.status() == WL_CONNECTED;
});
```

---

### `void markCriticalError(String msg);`
Immediately triggers Safe Mode due to a fatal error.

---

### `void enterManualSafeMode();`
Manually enters Safe Mode (from UI, network, or command).

---

### `bool inSafeMode();`
Returns `true` if device is currently in Safe Mode.

---

### `String getLastResetReason();`
Returns human-readable reason for failure:
- `"No fail"`
- `"Loop timeout"`
- `"Critical error"`
- `"Manual trigger"`

---

## 🧪 Example: Basic Watchdog

```cpp
void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("Safe Mode!");
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  digitalWrite(RELAY_PIN, HIGH);
  failsafe.feed();
  delay(1000);
}
```

---

## 🛠 Future Improvements

- [ ] NVS-based persistent error logging  
- [ ] Safe Mode callback (`onSafeModeEnter()`)  
- [ ] Integration with MQTT / Dashboard alerts  
- [ ] Auto-restart options

---

## 🔒 Safety First

You should **always** implement safety fallbacks in hardware (like relays, fuses, or timers),  
but software fail-safes like this library help ensure more **intelligent** and **predictable behavior** when unexpected issues happen.

---

## 👨‍💻 Author

Made with ❤️ by [Erfan Ganji](https://github.com/ErfanGanji87)  
Telegram: `@ErfanGanji2`  
GitHub: [# 🛡 ESP32FailSafe

**ESP32FailSafe** is a lightweight yet powerful fail-safe & watchdog system for critical ESP32-based projects.  
It actively monitors your main loop and essential subsystems (like sensors or communication) and automatically switches the device to **Safe Mode** in case of errors, delays, or failures.

---

## 🚨 Why Fail-Safe Matters

When building industrial, smart home, or robotics applications with ESP32, even a small software bug or sensor disconnect can lead to dangerous behaviors like:
- Motors running wild  
- Relays staying ON too long  
- Stuck loops or frozen Wi-Fi communication

This library ensures your system is always **under control** — and **shuts down safely** if it's not.

---

## ✅ Features

- ⏱️ **Loop watchdog:** Detects if the `loop()` is stuck or slow  
- 🧪 **Health checks:** Custom checks for sensors, logic, or connectivity  
- 🛑 **Safe Mode engine:** Executes only minimal code when fault detected  
- 📄 **Error logging:** Provides detailed reason for failure  
- 🧠 **Manual trigger:** Put device into Safe Mode from UI, button, or network  
- 🔄 **Extendable:** Minimal and modular C++ design

---

## 🔧 Installation

1. Copy the `ESP32FailSafe.h` and `ESP32FailSafe.cpp` to your project folder  
2. Or install it via GitHub:


git clone https://github.com/ErfanGanji87/ESP32FailSafe


Then include it in your sketch:

```cpp
#include <ESP32FailSafe.h>
```

---

## 🚀 Quick Start

```cpp
#include <ESP32FailSafe.h>

ESP32FailSafe failsafe;

void setup() {
  Serial.begin(115200);
  failsafe.begin(5000); // 5s timeout for loop

  failsafe.registerCheck("TemperatureSensor", []() {
    return analogRead(34) > 100; // Check your sensor
  });
}

void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("⚠ Safe mode active");
    return;
  }

  // Normal operation
  failsafe.feed();
  delay(1000);
}
```

---

## 🧩 API Reference

### `void begin(unsigned long loopTimeoutMs = 3000);`
Initializes the library.  
- `loopTimeoutMs`: maximum time (in ms) allowed between `feed()` calls.

---

### `void feed();`
Must be called regularly inside `loop()` to avoid watchdog timeout.

---

### `void registerCheck(String name, std::function<bool()> checkFunc);`
Registers a function to validate the health of a component.

```cpp
failsafe.registerCheck("WiFi", []() {
  return WiFi.status() == WL_CONNECTED;
});
```

---

### `void markCriticalError(String msg);`
Immediately triggers Safe Mode due to a fatal error.

---

### `void enterManualSafeMode();`
Manually enters Safe Mode (from UI, network, or command).

---

### `bool inSafeMode();`
Returns `true` if device is currently in Safe Mode.

---

### `String getLastResetReason();`
Returns human-readable reason for failure:
- `"No fail"`
- `"Loop timeout"`
- `"Critical error"`
- `"Manual trigger"`

---

## 🧪 Example: Basic Watchdog

```cpp
void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("Safe Mode!");
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  digitalWrite(RELAY_PIN, HIGH);
  failsafe.feed();
  delay(1000);
}
```

---

## 🛠 Future Improvements

- [ ] NVS-based persistent error logging  
- [ ] Safe Mode callback (`onSafeModeEnter()`)  
- [ ] Integration with MQTT / Dashboard alerts  
- [ ] Auto-restart options

---

## 🔒 Safety First

You should **always** implement safety fallbacks in hardware (like relays, fuses, or timers),  
but software fail-safes like this library help ensure more **intelligent** and **predictable behavior** when unexpected issues happen.

---

## 👨‍💻 Author

Made with ❤️ by [Erfan Ganji](https://github.com/ErfanGanji87)  
Telegram: `@ErfanGanji2`  
GitHub: (# 🛡 ESP32FailSafe

**ESP32FailSafe** is a lightweight yet powerful fail-safe & watchdog system for critical ESP32-based projects.  
It actively monitors your main loop and essential subsystems (like sensors or communication) and automatically switches the device to **Safe Mode** in case of errors, delays, or failures.

---

## 🚨 Why Fail-Safe Matters

When building industrial, smart home, or robotics applications with ESP32, even a small software bug or sensor disconnect can lead to dangerous behaviors like:
- Motors running wild  
- Relays staying ON too long  
- Stuck loops or frozen Wi-Fi communication

This library ensures your system is always **under control** — and **shuts down safely** if it's not.

---

## ✅ Features

- ⏱️ **Loop watchdog:** Detects if the `loop()` is stuck or slow  
- 🧪 **Health checks:** Custom checks for sensors, logic, or connectivity  
- 🛑 **Safe Mode engine:** Executes only minimal code when fault detected  
- 📄 **Error logging:** Provides detailed reason for failure  
- 🧠 **Manual trigger:** Put device into Safe Mode from UI, button, or network  
- 🔄 **Extendable:** Minimal and modular C++ design

---

## 🔧 Installation

1. Copy the `ESP32FailSafe.h` and `ESP32FailSafe.cpp` to your project folder  
2. Or install it via GitHub:


git clone https://github.com/ErfanGanji87/ESP32FailSafe


Then include it in your sketch:

```cpp
#include <ESP32FailSafe.h>
```

---

## 🚀 Quick Start

```cpp
#include <ESP32FailSafe.h>

ESP32FailSafe failsafe;

void setup() {
  Serial.begin(115200);
  failsafe.begin(5000); // 5s timeout for loop

  failsafe.registerCheck("TemperatureSensor", []() {
    return analogRead(34) > 100; // Check your sensor
  });
}

void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("⚠ Safe mode active");
    return;
  }

  // Normal operation
  failsafe.feed();
  delay(1000);
}
```

---

## 🧩 API Reference

### `void begin(unsigned long loopTimeoutMs = 3000);`
Initializes the library.  
- `loopTimeoutMs`: maximum time (in ms) allowed between `feed()` calls.

---

### `void feed();`
Must be called regularly inside `loop()` to avoid watchdog timeout.

---

### `void registerCheck(String name, std::function<bool()> checkFunc);`
Registers a function to validate the health of a component.

```cpp
failsafe.registerCheck("WiFi", []() {
  return WiFi.status() == WL_CONNECTED;
});
```

---

### `void markCriticalError(String msg);`
Immediately triggers Safe Mode due to a fatal error.

---

### `void enterManualSafeMode();`
Manually enters Safe Mode (from UI, network, or command).

---

### `bool inSafeMode();`
Returns `true` if device is currently in Safe Mode.

---

### `String getLastResetReason();`
Returns human-readable reason for failure:
- `"No fail"`
- `"Loop timeout"`
- `"Critical error"`
- `"Manual trigger"`

---

## 🧪 Example: Basic Watchdog

```cpp
void loop() {
  if (failsafe.inSafeMode()) {
    Serial.println("Safe Mode!");
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  digitalWrite(RELAY_PIN, HIGH);
  failsafe.feed();
  delay(1000);
}
```

---

## 🛠 Future Improvements

- [ ] NVS-based persistent error logging  
- [ ] Safe Mode callback (`onSafeModeEnter()`)  
- [ ] Integration with MQTT / Dashboard alerts  
- [ ] Auto-restart options

---

## 🔒 Safety First

You should **always** implement safety fallbacks in hardware (like relays, fuses, or timers),  
but software fail-safes like this library help ensure more **intelligent** and **predictable behavior** when unexpected issues happen.

---

## 👨‍💻 Author

Made with ❤️ by [Erfan Ganji](https://github.com/ErfanGanji87)  
Telegram: `@ErfanGanji2`  
GitHub: [ErfanGanji87](https://github.com/ErfanGanji87)
)

