#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <vector>
#include "sensors/SensorInterface.h"

// Forward declaration of CommsOut (defined in another submodule)
class CommsOut;

#ifdef USE_DS18B20
#include "sensors/DS18B20_Temperature/DS18B20_Temperature.h"
#endif

class SensorManager {
private:
    struct SensorState {
        SensorInterface* sensor;
        float lastValue;
        unsigned long lastSentTime;
    };

    std::vector<SensorState> sensors;
    CommsOut* comms;  // Pointer to external comms object

    static const unsigned long MAX_SILENT_PERIOD_MS = 5000;

public:
    SensorManager(CommsOut* commsOut);
    ~SensorManager();

    void setup();
    void pollSensors();
};

#endif
