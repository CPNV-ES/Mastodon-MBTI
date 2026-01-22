#ifndef PS4MANAGER_H
#define PS4MANAGER_H

#include <Arduino.h>
#include <PS4Controller.h>

class LedBlinker;

class PS4Manager {
private:
    const int LED_PIN;
    const int LED_PIN_1;
    const int LED_PIN_2;
    unsigned long lastPrint;
    unsigned long lastBatteryCheck;
    LedBlinker* ledBlinker;
    static const int PRINT_INTERVAL = 1000;
    static const int BATTERY_CHECK_INTERVAL = 30000;

public:
    PS4Manager(int ledPin, int ledPin1, int ledPin2);

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

#endif