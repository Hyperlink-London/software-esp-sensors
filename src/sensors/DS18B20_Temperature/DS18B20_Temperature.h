#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#if DEBUG
    #define debugp(...) Serial.print(__VA_ARGS__) 
    #define debugpln(...) Serial.println(__VA_ARGS__) 
    #define debugpf(...) Serial.printf(__VA_ARGS__) 
#else
    #define debugp(...) 
    #define debugpln(...)
    #define debugpf(...)
#endif

#include <NonBlockingDallas.h>
#include <SensorInterface.h>

class DS18B20_Temperature : public NonBlockingDallas, public SensorInterface {
private:
    DallasTemperature dallasTemp;
    OneWire onewire;

    float tC;
    static float* tC_ptr;

public:
    DS18B20_Temperature(uint8_t pin);
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
    static void handleIntervalElapsed(float temperature, bool valid, int deviceIndex);
    void printTemperature();
};

#endif
