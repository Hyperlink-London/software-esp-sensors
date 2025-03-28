#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <Arduino.h>

class SensorInterface {
public:
    virtual void setup() = 0;               // Called during system setup
    virtual void update() = 0;              // Called periodically to refresh data
    virtual float getVal() const = 0;       // Return the most recent sensor reading
    virtual String getName() const = 0;     // Human-readable sensor name
    virtual ~SensorInterface() {}           // Virtual destructor for safe cleanup
};

#endif
