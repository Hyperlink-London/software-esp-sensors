# Sensors Library

This repository contains the `sensors` module used in the Hyperlink Firmware systems. It provides sensor management functionality and implements the `SensorManager` class, which handles the setup, polling, and reporting of sensor data in a general and modular fashion.

This library is designed to be flexible and extensible. It supports dynamically enabling or disabling specific sensors at compile time using `#define` flags and uses a standard interface to communicate with other modules such as `CommsOut`.

## Repository Structure

```
sensors/
├── src/
│   ├── SensorManager.h
│   ├── SensorManager.cpp
│   ├── sensors/
│   │   └── <SensorName>/
│   │       ├── <SensorName>.h
│   │       └── <SensorName>.cpp
├── library.properties
└── README.md
```

- `SensorManager.h/cpp`: Core logic for managing sensor setup and polling. Integrates all registered sensors and handles update logic.
- `sensors/`: Contains folders for individual sensor drivers, each implementing the shared sensor interface.
- `library.properties`: Metadata for Arduino CLI and IDE compatibility.


## Purpose

This library provides a hardware-agnostic, interface-driven framework for integrating and managing multiple sensors on an ESP32. It supports:

- Conditional inclusion of sensors at compile time
- A consistent interface for accessing sensor data
- Automatic polling and update control based on value changes or time intervals
- Integration with outbound communication interfaces (e.g., `CommsOut`)

## Design and Interfaces

### SensorInterface (defined in the `interfaces` submodule)

Each sensor must implement the following interface, which is defined in the shared `interfaces` module:

```cpp
class SensorInterface {
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual float getVal() = 0;
    virtual String getName() = 0;
    virtual ~SensorInterface() = default;
};
```

This interface allows `SensorManager` to generically manage different sensor types without knowing implementation details.

### SensorManager

```cpp
class SensorManager {
public:
    SensorManager(CommsOutInterface* comms);
    ~SensorManager();
    void setup();
    void pollSensors();
};
```

- `setup()`: Initialises all enabled sensors.
- `pollSensors()`: Updates sensors, checks for value changes, and forwards data via the communication interface.

---

## Usage Example

Used in an Arduino sketch or embedded system:

```cpp
#include <SensorManager.h>
#include <CommsOut.h>

CommsOut comms;
SensorManager manager(&comms);

void setup() {
    Serial.begin(115200);
    manager.setup();
}

void loop() {
    manager.pollSensors();
    delay(1000);
}
```

---

## Optional Sensor Activation

Sensors can be conditionally compiled using preprocessor flags (e.g., defined in a global header or build script):

```cpp
#define USE_SENSOR_X
```

Only sensors explicitly enabled will be instantiated and managed by the system.

---

## Development Notes

- Each sensor driver must reside in its own subdirectory under `src/` and implement `SensorInterface` (from the `interfaces` module).
- `SensorManager` owns the lifecycle and update policy for all registered sensors.
- The library is designed to remain decoupled from any specific communication protocol or backend; all data flows through the abstract `CommsOutInterface`.
