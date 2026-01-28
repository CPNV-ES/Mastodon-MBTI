#ifndef AUTOMODECONTROLLER_H
#define AUTOMODECONTROLLER_H

#include <Arduino.h>

class MotorController;
class DirectionController;
class UltrasonicController;

class AutoModeController {
private:
    enum State { FORWARD, REVERSING, TURNING, STOPPED };
    State currentState;
    bool isAutoModeActive;
    unsigned long stateStartTime;
    
    MotorController* motorController;
    DirectionController* directionController;
    UltrasonicController* ultrasonicController;
    
    const float OBSTACLE_THRESHOLD = 20.0; // cm
    const int FORWARD_SPEED = 150;
    const int REVERSE_SPEED = -120;
    const unsigned long REVERSE_DURATION = 1000; // ms
    const unsigned long TURN_DURATION = 500; // ms
    
public:
    AutoModeController(MotorController* motor, DirectionController* direction, UltrasonicController* ultrasonic);
    void begin();
    void toggle();
    void update();
    bool isActive() const;
};

#endif