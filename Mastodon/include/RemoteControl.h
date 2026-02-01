#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <Arduino.h>
#include <PS4Controller.h>

class Blinkers;
class Steering;
class Lights;
class Motor;
class AutoMode;

class RemoteControl {
private:
    const int LED_PIN;
    const int LED_PIN_1;
    const int LED_PIN_2;
    unsigned long lastPrint;
    const int PRINT_INTERVAL = 100; // ms
    unsigned long lastBatteryCheck;
    const unsigned long BATTERY_CHECK_INTERVAL = 10000; // 10 seconds

    Blinkers* blinkers;
    Steering* steering;
    Lights* lights;
    Motor* motor;
    AutoMode* autoMode;

    bool obstacleDetected;

    bool lastL1State;
    bool lastR1State;
    bool lastTriangleState;
    bool lastOptionsState;

public:
    RemoteControl(int ledPin, int ledPin1, int ledPin2);

    void begin(const char* macAddress);

    void setBlinkers(Blinkers* blinker);

    void setSteering(Steering* controller);

    void setLights(Lights* controller);

    void setMotor(Motor* controller);

    void setAutoMode(AutoMode* controller);
    
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