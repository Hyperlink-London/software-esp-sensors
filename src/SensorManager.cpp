#include "SensorManager.h"

SensorManager::SensorManager(CommsOutInterface* commsOut)
    : comms(commsOut), pinsValidated(false)
{
#ifdef USE_DEMO
    int demo_pins[] = DEMO_PINS;
    SensorInterface* demo_sensor = new Demo(demo_pins[0], demo_pins[1]);
    sensors.push_back({ demo_sensor, NAN, 0 });
#endif
#ifdef USE_DEMO_TWO
    int demo_two_pins[] = DEMO_TWO_PINS;
    SensorInterface* demo_sensor_two = new DemoTwo(demo_two_pins[0], demo_two_pins[1], demo_two_pins[2]);
    sensors.push_back({ demo_sensor_two, NAN, 0 });
#endif

    // Validate pins immediately after sensor creation
    pinsValidated = validatePins();
    
    if (!pinsValidated) {
        Serial_1.println("WARNING: Pin validation failed! SensorManager will not operate on core 0.");
        Serial_1.println("Fix pin conflicts before system can function properly.");
    }
}

SensorManager::~SensorManager() {
    for (auto& s : sensors) {
        delete s.sensor;
    }
}

void SensorManager::setup() {
    if (!pinsValidated) {
        Serial_1.println("ERROR: Cannot setup sensors - pin validation failed!");
        Serial_1.println("Fix pin conflicts and restart the system.");
        return;
    }
    
    Serial_1.println("Setting up sensors...");
    for (auto& s : sensors) {
        s.sensor->setup();
    }
    Serial_1.println("Sensor setup complete.");
    // TODO: send msg to OBC to say it has setup
}

void SensorManager::pollSensors() {
    unsigned long now = millis();

    for (auto& s : sensors) {
        s.sensor->update();
        float val = s.sensor->getVal();

        bool isNewValue = isnan(s.lastValue) || val != s.lastValue;
        bool isStale = (now - s.lastSentTime) >= MAX_SILENT_PERIOD_MS;

        if (isNewValue || isStale) {
            comms->send(s.sensor->getName(), val);  // Send via interface
            s.lastValue = val;
            s.lastSentTime = now;
        }
    }
}

bool SensorManager::validatePins() {
    std::vector<int> allPins;
    std::vector<String> sensorNames;
    
    // Collect all pins and their corresponding sensor names
    for (const auto& sensorState : sensors) {
        std::vector<int> sensorPins = sensorState.sensor->getPins();
        String sensorName = sensorState.sensor->getName();
        
        for (int pin : sensorPins) {
            allPins.push_back(pin);
            sensorNames.push_back(sensorName);
        }
    }
    
    // Check for duplicates and report which sensors are conflicting
    bool hasConflicts = false;
    
    for (size_t i = 0; i < allPins.size(); i++) {
        for (size_t j = i + 1; j < allPins.size(); j++) {
            if (allPins[i] == allPins[j]) {
                hasConflicts = true;
                Serial_1.print("ERROR: Pin conflict detected! Pin ");
                Serial_1.print(allPins[i]);
                Serial_1.print(" is used by both '");
                Serial_1.print(sensorNames[i]);
                Serial_1.print("' and '");
                Serial_1.print(sensorNames[j]);
                Serial_1.println("' sensors.");
            }
        }
    }
    
    if (!hasConflicts) {
        Serial_1.println("Pin validation passed - no conflicts detected.");
        Serial_1.print("Total pins in use: ");
        Serial_1.println(allPins.size());
    }
    
    return !hasConflicts;
}

bool SensorManager::arePinsValidated() const {
    return pinsValidated;
}
