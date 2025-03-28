#include "demoTwo.h"

void DemoTwo::setup() {
    // do nothing
}

void DemoTwo::update() {
    // get a radom float value between 0 and 100
    demo_val = random(0, 100) / 10.0;
}

float DemoTwo::getVal() const {
    return demo_val;
}

String DemoTwo::getName() const {
    return "DemoTwo";
}