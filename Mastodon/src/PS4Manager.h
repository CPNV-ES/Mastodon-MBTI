#ifndef PS4MANAGER_H
#define PS4MANAGER_H

#include <Arduino.h>
#include <PS4Controller.h>

class LedBlinker;
class DirectionController;

class PS4Manager {
private:
    const int LED_PIN;
    unsigned long lastPrint;
    const int PRINT_INTERVAL = 100; // ms
    unsigned long lastBatteryCheck;
    const unsigned long BATTERY_CHECK_INTERVAL = 10000; // 10 seconds
    
    LedBlinker* ledBlinker;
    DirectionController* directionController;
    
public:
    PS4Manager(int ledPin);
    
    void begin(const char* macAddress);
    
    void setLedBlinker(LedBlinker* blinker);
    
    void setDirectionController(DirectionController* controller);
    
    void update();
    
    bool isConnected();
    
private:
    void handleButtons();
    
    void handleJoysticks();
    
    void handleBattery();
    
    void handleDPad();
};

#endif