#include "LedController.h"

LedController::LedController(int brakePin, int fixedPin) 
    : brakeLightPin(brakePin), fixedLedPin(fixedPin), isBrakeOn(false) {}

void LedController::begin() {
    pinMode(brakeLightPin, OUTPUT);
    pinMode(fixedLedPin, OUTPUT);
    
    digitalWrite(brakeLightPin, LOW);
    digitalWrite(fixedLedPin, HIGH);
}

void LedController::startBrakeLights() {
    digitalWrite(brakeLightPin, HIGH);
    isBrakeOn = true;
}

void LedController::stopBrakeLights() {
    digitalWrite(brakeLightPin, LOW);
    isBrakeOn = false;
}

bool LedController::getBrakeLightsState() const {
    return isBrakeOn;
}