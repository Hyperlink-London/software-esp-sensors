#ifndef DEMOTWO_H
#define DEMOTWO_H

#include <SensorInterface.h>
#include <vector>

class DemoTwo : public SensorInterface {
private:
    float demo_val;
    int pin1, pin2, pin3;  // Example: sensor needs 3 pins

public:
    // Constructor with pin configuration
    DemoTwo(int p1, int p2, int p3) : pin1(p1), pin2(p2), pin3(p3) {}
    
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
    std::vector<int> getPins() const override;
};

#endif
