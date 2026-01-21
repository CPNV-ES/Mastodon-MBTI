#ifndef PS4MANAGER_H
#define PS4MANAGER_H

#include <Arduino.h>
#include <PS4Controller.h>

class LedBlinker;

class PS4Manager {
private:
    const int LED_PIN;
    unsigned long lastPrint;
    const int PRINT_INTERVAL = 100; // ms
    unsigned long lastBatteryCheck;
    const unsigned long BATTERY_CHECK_INTERVAL = 10000; // 10 seconds
    
    LedBlinker* ledBlinker;
    
public:
    PS4Manager(int ledPin);
    
    void begin(const char* macAddress);
    
    void setLedBlinker(LedBlinker* blinker);
    
    void update();
    
    bool isConnected();
    
private:
    void handleButtons();
    
    void handleJoysticks();
    
    void handleBattery();
    
    void handleDPad();
};
class PS4Manager {
private:
    int LED_PIN;
    int LED_PIN_1;  // Ajoutez cette ligne
    int LED_PIN_2;  // Ajoutez cette ligne
    unsigned long lastPrint;
    unsigned long lastBatteryCheck;
    LedBlinker* ledBlinker;
    static const int PRINT_INTERVAL = 1000;
    static const int BATTERY_CHECK_INTERVAL = 30000;

public:
    PS4Manager(int ledPin, int ledPin1, int ledPin2);  // Modifiez le constructeur
    // ... reste du code
};

#endif