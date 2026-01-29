#ifndef PS4MANAGER_H
#define PS4MANAGER_H

#include <Arduino.h>
#include <PS4Controller.h>

class LedBlinker;
class DirectionController;
class LedController;
class MotorController;
class AutoModeController;

class PS4Manager {
private:
    const int LED_PIN;
    const int LED_PIN_1;
    const int LED_PIN_2;
    unsigned long lastPrint;
    const int PRINT_INTERVAL = 100; // ms
    unsigned long lastBatteryCheck;
    const unsigned long BATTERY_CHECK_INTERVAL = 10000; // 10 seconds

    LedBlinker* ledBlinker;
    DirectionController* directionController;
    LedController* ledController;
    MotorController* motorController;
    AutoModeController* autoModeController;
    
    bool obstacleDetected;
    
    bool lastL1State;
    bool lastR1State;
    bool lastTriangleState;
    bool lastOptionsState;
    
public:
    PS4Manager(int ledPin, int ledPin1, int ledPin2);

    void begin(const char* macAddress);

    void setLedBlinker(LedBlinker* blinker);
    
    void setDirectionController(DirectionController* controller);

    void setLedController(LedController* Controller);
    
    void setMotorController(MotorController* controller);
    
    void setAutoModeController(AutoModeController* controller);
    
    void setObstacleDetected(bool detected);
    
    void update();

    bool isConnected();

private:
    void handleButtons();
    void handleJoysticks();
    void handleBattery();
    void handleDPad();
};

#endif