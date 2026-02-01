#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic {
private:
    int trigPin;
    int echoPin;
    const float SOUND_SPEED = 0.034;

public:
    Ultrasonic(int trig, int echo);
    void begin();
    float getDistance();
    bool isObstacleDetected(float thresholdCm);
};

#endif