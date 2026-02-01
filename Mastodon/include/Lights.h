#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>

class Lights {
private:
    int brakeLightPin;
    int fixedLedPin;
    int rgbRedPin1;
    int rgbGreenPin1;
    int rgbBluePin1;
    bool isBrakeOn;

public:
    Lights(int brakePin, int fixedPin, int r1, int g1, int b1);
    void begin();
    void startBrakeLights();
    void stopBrakeLights();
    bool getBrakeLightsState() const;
};

#endif