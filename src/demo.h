#ifndef DEMO_H
#define DEMO_H

#include <SensorInterface.h>

class Demo : public SensorInterface {
private:
    float demo_val;

public:
    void setup() override;
    void update() override;
    float getVal() const override;
    String getName() const override;
};

#endif
