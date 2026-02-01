#include "Motor.h"
#include "Blinkers.h"

Motor::Motor(int pin1, int pin2, int enable)
    : motorPin1(pin1), motorPin2(pin2), enablePin(enable), isStopped(true), currentSpeed(0), blinkers(nullptr) {}

void Motor::begin() {
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(enablePin, OUTPUT);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    analogWrite(enablePin, 0);

    Serial.println("[MOTOR] Motor initialized");
}

void Motor::setSpeed(int speed) {
    if (isStopped && speed != 0) {
        isStopped = false;
    }

    currentSpeed = constrain(speed, -255, 255);

    if (currentSpeed > 0) {
        // Forward
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        analogWrite(enablePin, currentSpeed);
    } else if (currentSpeed < 0) {
        // Backward
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        analogWrite(enablePin, abs(currentSpeed));
    } else {
        // Stop
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        analogWrite(enablePin, 0);
        isStopped = true;
    }
}

void Motor::emergencyStop() {
    if (blinkers != nullptr) {
        blinkers->toggleWarningLights();
    }

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    analogWrite(enablePin, 200);
    delay(150);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    analogWrite(enablePin, 0);
    currentSpeed = 0;
    isStopped = true;
    Serial.println("[MOTOR] Emergency stop - Obstacle detected!");
}

void Motor::setBlinkers(Blinkers* blinker) {
    blinkers = blinker;
}

void Motor::brake() {
    setSpeed(0);
    Serial.println("[MOTOR] Braking");
}

bool Motor::isStoppedState() const {
    return isStopped;
}