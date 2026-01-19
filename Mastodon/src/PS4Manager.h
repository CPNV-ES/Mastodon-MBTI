#ifndef PS4MANAGER_H
#define PS4MANAGER_H

#include <Arduino.h>
#include <PS4Controller.h>

class PS4Manager {
private:
    const int LED_PIN;
    unsigned long lastPrint;
    const int PRINT_INTERVAL = 100; // ms
    unsigned long lastBatteryCheck;
    const unsigned long BATTERY_CHECK_INTERVAL = 10000; // 10 seconds
    
public:
    PS4Manager(int ledPin);

    void begin(const char* macAddress);
    
    void update();
    
    bool isConnected();
    
private:
    void handleButtons();
    
    void handleJoysticks();
    
    void handleBattery();
    
    void handleDPad();
};

#endif