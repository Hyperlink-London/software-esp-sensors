#include "DS18B20_Temperature.h"

float* DS18B20_Temperature::tC_ptr = nullptr;

DS18B20_Temperature::DS18B20_Temperature(uint8_t pin) : NonBlockingDallas(&dallasTemp) {
    onewire.begin(pin);
    dallasTemp.setOneWire(&onewire);
    tC_ptr = &tC;
}

void DS18B20_Temperature::setup() {
    begin(NonBlockingDallas::resolution_10, NonBlockingDallas::unit_C, 1500);
    onIntervalElapsed(handleIntervalElapsed);
}

void DS18B20_Temperature::update() {
    NonBlockingDallas::update(); // Required for non-blocking temperature polling
}

float DS18B20_Temperature::getVal() const {
    return tC;
}

String DS18B20_Temperature::getName() const {
    return "DS18B20";
}

void DS18B20_Temperature::handleIntervalElapsed(float temperature, bool valid, int deviceIndex) {
    if (tC_ptr != nullptr) {
        *tC_ptr = temperature;
    }
}

void DS18B20_Temperature::printTemperature() {
    debugpf("Temperature: %.2f\n", tC);
}
