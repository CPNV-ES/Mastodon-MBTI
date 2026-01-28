#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int brakeLightPin;
    int fixedLedPin;
    int rgbRedPin1;
    int rgbGreenPin1;
    int rgbBluePin1;
    bool isBrakeOn;

public:
    LedController(int brakePin, int fixedPin, int r1, int g1, int b1);
    void begin();
    void startBrakeLights();
    void stopBrakeLights();
    bool getBrakeLightsState() const;
};

#endif