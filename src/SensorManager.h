#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <vector>
#include <CommsOutInterface.h>  // From interfaces module
#include <SensorInterface.h>

#ifdef USE_DEMO
    #include "demo.h"
#endif
#ifdef USE_DEMO_TWO
    #include "demoTwo.h"
#endif

class SensorManager {
private:
    struct SensorState {
        SensorInterface* sensor;
        float lastValue;
        unsigned long lastSentTime;
    };

    std::vector<SensorState> sensors;
    CommsOutInterface* comms;  // Abstract interface, not a concrete type

    static const unsigned long MAX_SILENT_PERIOD_MS = 5000;

public:
    SensorManager(CommsOutInterface* commsOut);
    ~SensorManager();

    void setup();
    void pollSensors();
};

#endif
