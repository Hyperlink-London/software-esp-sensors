// Comment out the sensors which are not being used
#define USE_DEMO
#define USE_DEMO_TWO

#include "SensorManager.h"

SensorManager::SensorManager(CommsOutInterface* commsOut)
    : comms(commsOut)
{
#ifdef USE_DEMO
    SensorInterface* demo_sensor = new Demo();
    sensors.push_back({ demo_sensor, NAN, 0 });
#endif
#ifdef USE_DEMO_TWO
    SensorInterface* demo_sensor_two = new DemoTwo();
    sensors.push_back({ demo_sensor_two, NAN, 0 });
#endif
}

SensorManager::~SensorManager() {
    for (auto& s : sensors) {
        delete s.sensor;
    }
}

void SensorManager::setup() {
    for (auto& s : sensors) {
        s.sensor->setup();
    }
}

void SensorManager::pollSensors() {
    unsigned long now = millis();

    for (auto& s : sensors) {
        s.sensor->update();
        float val = s.sensor->getVal();

        bool isNewValue = isnan(s.lastValue) || val != s.lastValue;
        bool isStale = (now - s.lastSentTime) >= MAX_SILENT_PERIOD_MS;

        if (isNewValue || isStale) {
            comms->send(s.sensor->getName(), val);  // Send via interface
            s.lastValue = val;
            s.lastSentTime = now;
        }
    }
}
