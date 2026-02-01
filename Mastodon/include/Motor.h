#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Blinkers;

class Motor {
private:
    int motorPin1;
    int motorPin2;
    int enablePin;
    bool isStopped;
    int currentSpeed;

    Blinkers* blinkers;

public:
    Motor(int pin1, int pin2, int enable);
    void begin();
    void setSpeed(int speed); // -255 to 255
    void emergencyStop();
    void brake();
    bool isStoppedState() const;
    void setBlinkers(Blinkers* blinker);
};

#endif