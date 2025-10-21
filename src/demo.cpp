#include "demo.h"

void Demo::setup() {
    pinMode(pin1, INPUT);
    pinMode(pin2, OUTPUT);
}

void Demo::update() {
    // TODO: use pins
    
    // get a radom float value between 0 and 100
    demo_val = random(0, 100) / 10.0;
}

float Demo::getVal() const {
    return demo_val;
}

String Demo::getName() const {
    return "demo";
}

std::vector<int> Demo::getPins() const {
    return {pin1, pin2};
}