#ifndef AUTOMODE_H
#define AUTOMODE_H

#include <Arduino.h>

class Motor;
class Steering;
class Ultrasonic;

class AutoMode {
private:
    enum State { FORWARD, REVERSING, TURNING, STOPPED };
    State currentState;
    bool isAutoModeActive;
    unsigned long stateStartTime;

    Motor* motor;
    Steering* steering;
    Ultrasonic* ultrasonic;

    const float OBSTACLE_THRESHOLD = 20.0; // cm
    const int FORWARD_SPEED = 150;
    const int REVERSE_SPEED = -150;
    const unsigned long REVERSE_DURATION = 5000; // ms
    const unsigned long TURN_DURATION = 5000; // ms

public:
    AutoMode(Motor* motorCtrl, Steering* steeringCtrl, Ultrasonic* ultrasonicCtrl);
    void begin();
    void toggle();
    void update();
    bool isActive() const;
};

#endif