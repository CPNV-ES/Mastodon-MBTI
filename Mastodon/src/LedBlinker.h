#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include <Arduino.h>

class LedBlinker {
private:
    const int led1;
    const int led2;
    const int led4;
    
    bool isBlinking;
    
    unsigned long previousMillis;
    const long interval = 300;
    bool ledState;
    
    enum BlinkerSide { NONE, LEFT, RIGHT, BOTH };
    BlinkerSide activeBlinker;
    
public:
    LedBlinker(int led1Pin, int led2Pin, int led4Pin);
    
    void begin();
    
    void update();
    
    bool getBlinkState() const { return isBlinking; }
    
    void startLeftBlinker();
    void startRightBlinker();
    void stopBlinkers();
    
private:
    void updateLeds();
};

#endif