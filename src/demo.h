#ifndef DEMO_H
#define DEMO_H

#include <SensorInterface.h>
#include <vector>

class Demo : public SensorInterface {
private:
    float demo_val;
    int pin1, pin2;  // Example: sensor needs 2 pins

public:
    // Constructor with pin configuration
    Demo(int p1, int p2) : pin1(p1), pin2(p2) {}
    
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
    std::vector<int> getPins() const override;
};

#endif
