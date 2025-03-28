#include "DS18B20.h"

float* DS18B20_Temperature::tC_ptr = nullptr;

DS18B20_Temperature::DS18B20_Temperature(uint8_t pin) : NonBlockingDallas(&dallasTemp) {
    onewire.begin(pin);
    dallasTemp.setOneWire(&onewire);
    tC_ptr = &tC;
}

void DS18B20_Temperature::setup() {
    begin(NonBlockingDallas::resolution_10, NonBlockingDallas::unit_C, 1500);
    onIntervalElapsed(handleIntervalElapsed);
    // onTemperatureChange(handleTemperatureChange);
    // onDeviceDisconnected(handleDeviceDisconnected);
}

void DS18B20_Temperature::handleIntervalElapsed(float temperature, bool valid, int deviceIndex) {
    if (tC_ptr != nullptr) {
        *tC_ptr = temperature;
    }
}

void DS18B20_Temperature::printTemperature() {
    debugpf("Temperature: %.2f\n", tC);
}
