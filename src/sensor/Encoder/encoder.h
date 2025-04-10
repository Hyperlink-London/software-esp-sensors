#pragma once
#include <Arduino.h>
#include "../interfaces/src/SensorInterface.h"

class Encoder : public SensorInterface
{
private:
    int channelA_pin;
    int channelB_pin;
    int switch_pin;
    int resolution;
    volatile long position;
    bool switchState;

public:
    Encoder(int pinA, int pinB, int pinSwitch, int ppr = 32);

    bool initialize();
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
};