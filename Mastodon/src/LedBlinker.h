#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include <Arduino.h>

class LedBlinker {
private:
    const int leftBlinkerPin;
    const int rightBlinkerPin;
    
    bool isBlinking;
    
    unsigned long previousMillis;
    const long interval = 300;
    bool ledState;
    
    enum BlinkerSide { NONE, LEFT, RIGHT, BOTH };
    BlinkerSide activeBlinker;
    
public:
    LedBlinker(int leftPin, int rightPin);
    
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