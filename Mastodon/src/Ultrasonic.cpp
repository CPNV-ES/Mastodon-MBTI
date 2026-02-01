#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo)
    : trigPin(trig), echoPin(echo) {}

void Ultrasonic::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.println("[ULTRASONIC] Sensor initialized");
}

float Ultrasonic::getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duree = pulseIn(echoPin, HIGH, 30000);

    if (duree == 0) {
        return -1;
    }

    float distance = (duree * SOUND_SPEED) / 2;

    // Out of range
    if (distance > 400) {
        return -1;
    }

    return distance;
}

bool Ultrasonic::isObstacleDetected(float thresholdCm) {
    float distance = getDistance();
    
    if (distance == -1) {
        return false;
    }
    
    return distance < thresholdCm;
}