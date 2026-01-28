#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController {
private:
    int motorPin1;
    int motorPin2;
    int enablePin;
    bool isStopped;
    int currentSpeed;
    
public:
    MotorController(int pin1, int pin2, int enable);
    void begin();
    void setSpeed(int speed); // -255 to 255
    void emergencyStop();
    void brake();
    bool isStoppedState() const;
};

#endif