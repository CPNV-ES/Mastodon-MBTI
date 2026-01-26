#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int led3;
    bool isBrakeOn;

public:
    LedController(int led3pin);
    void begin();
    void startBrakeLights();
    void stopBrakeLights();
    bool getBrakeLightsState() const;
};

#endif