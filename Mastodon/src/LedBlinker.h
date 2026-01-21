#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include <Arduino.h>

class LedBlinker {
private:
    const int led1;
    const int led2;
    const int led3;
    const int led4;
    
    const int buttonPin;
    
    bool isBlinking;
    int lastButtonState;
    unsigned long buttonPressedTime;
    const long longPressDuration = 2000; // 2 seconds 
    bool isPressing;
    
    unsigned long previousMillis;
    const long interval = 300;
    bool ledState;
    
    enum BlinkerSide { NONE, LEFT, RIGHT, BOTH };
    BlinkerSide activeBlinker;
    
public:
    LedBlinker(int led1Pin, int led2Pin, int led3Pin, int led4Pin, int btnPin);
    
    void begin();
    
    void update();
    
    bool getBlinkState() const { return isBlinking; }
    
    void startLeftBlinker();
    void startRightBlinker();
    void stopBlinkers();
    
private:
    void handleButton();
    
    void updateLeds();
};

#endif