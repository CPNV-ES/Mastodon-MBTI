#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int brakeLightPin;
    int fixedLedPin;
    bool isBrakeOn;

public:
    LedController(int brakePin, int fixedPin);
    void begin();
    void startBrakeLights();
    void stopBrakeLights();
    bool getBrakeLightsState() const;
};

#endif