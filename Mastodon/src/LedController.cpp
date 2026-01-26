#include "LedController.h"

LedController::LedController(int led3pin) 
    : led3(led3pin), isBrakeOn(false) {}

void LedController::begin() {
    pinMode(led3, OUTPUT);
    digitalWrite(led3, LOW);
}

void LedController::startBrakeLights() {
    digitalWrite(led3, HIGH);
    isBrakeOn = true;
}

void LedController::stopBrakeLights() {
    digitalWrite(led3, LOW);
    isBrakeOn = false;
}

bool LedController::getBrakeLightsState() const {
    return isBrakeOn;
}