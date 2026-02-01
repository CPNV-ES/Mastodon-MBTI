#ifndef STEERING_H
#define STEERING_H

#include <Arduino.h>
#include <ESP32Servo.h>

class Steering {
private:
    Servo servo;
    const int SERVO_PIN;

    static const int SERVO_CENTER_DEG = 90;
    static const int SERVO_CENTER_OFFSET_DEG = 5;
    static const int SERVO_MAX_DEG = 15;
    static const int ATTACH_MIN_US = 500;
    static const int ATTACH_MAX_US = 2500;

    static const int JOYSTICK_DEADZONE = 20;

    int currentDirection;

    int clampInt(int v, int lo, int hi);
    int dirToAngleDeg(int direction);

public:
    Steering(int servoPin);
    
    void begin();
    
    void setDirection(int direction);
    
    void setDirectionFromJoystick(int joystickX);
    
    int getCurrentDirection() const;
};

#endif