#ifndef BLINKERS_H
#define BLINKERS_H

#include <Arduino.h>

class Blinkers {
private:
    const int leftBlinkerPin;
    const int rightBlinkerPin;
    const int leftBlinkerPin2;
    const int rightBlinkerPin2;

    bool isBlinking;

    unsigned long previousMillis;
    const long interval = 300;
    bool ledState;

    enum BlinkerSide { NONE, LEFT, RIGHT, BOTH };
    BlinkerSide activeBlinker;

public:
    Blinkers(int leftPin, int rightPin, int leftPin2, int rightPin2);
    
    void begin();
    
    void update();
    
    bool getBlinkState() const { return isBlinking; }
    
    void toggleLeftBlinker();
    void toggleRightBlinker();
    void toggleWarningLights();
    void stopBlinkers();
    
private:
    void updateLeds();
};

#endif