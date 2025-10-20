#include "demo.h"

void Demo::setup() {
    // TODO: setup pins here
}

void Demo::update() {
    // get a radom float value between 0 and 100
    demo_val = random(0, 100) / 10.0;
}

float Demo::getVal() const {
    return demo_val;
}

String Demo::getName() const {
    return "demo";
}