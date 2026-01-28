#ifndef ULTRASONICCONTROLLER_H
#define ULTRASONICCONTROLLER_H

#include <Arduino.h>

class UltrasonicController {
private:
    int trigPin;
    int echoPin;
    const float SOUND_SPEED = 0.034;
    
public:
    UltrasonicController(int trig, int echo);
    void begin();
    float getDistance();
    bool isObstacleDetected(float thresholdCm);
};

#endif