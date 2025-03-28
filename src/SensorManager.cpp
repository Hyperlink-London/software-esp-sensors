#include "SensorManager.h"

SensorManager::SensorManager() {
#ifdef USE_DS18B20
    const uint8_t DS18B20_pin = 4;
    SensorInterface* DS18B20_temp_sensor = new DS18B20_Temperature(DS18B20_pin);
    sensors.push_back({ DS18B20_temp_sensor, NAN, 0 });
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
            // comms.send(s.sensor->getName(), val);
            s.lastValue = val;
            s.lastSentTime = now;
        }
    }
}
