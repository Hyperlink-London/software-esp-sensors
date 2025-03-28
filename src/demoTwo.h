#ifndef DEMOTWO_H
#define DEMOTWO_H

#include <SensorInterface.h>

class DemoTwo : public SensorInterface {
private:
    float demo_val;

public:
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
};

#endif
