#include "demoTwo.h"

void DemoTwo::setup() {
    pinMode(pin1, INPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, INPUT_PULLUP);
}

void DemoTwo::update() {
    // TODO: use pins

    // get a radom float value between 0 and 100
    demo_val = random(0, 100) / 10.0;
}

float DemoTwo::getVal() const {
    return demo_val;
}

String DemoTwo::getName() const {
    return "DemoTwo";
}

std::vector<int> DemoTwo::getPins() const {
    return {pin1, pin2, pin3};
}