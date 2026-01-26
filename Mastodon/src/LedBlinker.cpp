#include "LedBlinker.h"

LedBlinker::LedBlinker(int leftPin, int rightPin)
    : leftBlinkerPin(leftPin), rightBlinkerPin(rightPin),
      isBlinking(false), previousMillis(0), ledState(LOW), activeBlinker(NONE) {
}

void LedBlinker::begin() {
    pinMode(leftBlinkerPin, OUTPUT);
    pinMode(rightBlinkerPin, OUTPUT);
    
    digitalWrite(leftBlinkerPin, LOW);
    digitalWrite(rightBlinkerPin, LOW);
}

void LedBlinker::update() {
    updateLeds();
}

void LedBlinker::updateLeds() {
    unsigned long currentMillis = millis();
    
    if (isBlinking) {
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            ledState = !ledState;
            
            switch (activeBlinker) {
                case LEFT:
                    digitalWrite(leftBlinkerPin, ledState);
                    digitalWrite(rightBlinkerPin, LOW);
                    break;
                    
                case RIGHT:
                    digitalWrite(leftBlinkerPin, LOW);
                    digitalWrite(rightBlinkerPin, ledState);
                    break;
                    
                case BOTH:
                    digitalWrite(leftBlinkerPin, ledState);
                    digitalWrite(rightBlinkerPin, ledState);
                    break;
                    
                case NONE:
                default:
                    digitalWrite(leftBlinkerPin, LOW);
                    digitalWrite(rightBlinkerPin, LOW);
                    break;
            }
        }
    } else {
        digitalWrite(leftBlinkerPin, LOW);
        digitalWrite(rightBlinkerPin, LOW);
    }
}

void LedBlinker::toggleLeftBlinker() {
    if (activeBlinker == LEFT && isBlinking) {
        stopBlinkers();
        Serial.println("[BLINKER] Clignotant GAUCHE désactivé");
    } else {
        activeBlinker = LEFT;
        isBlinking = true;
        Serial.println("[BLINKER] Clignotant GAUCHE activé");
    }
}

void LedBlinker::toggleRightBlinker() {
    if (activeBlinker == RIGHT && isBlinking) {
        stopBlinkers();
        Serial.println("[BLINKER] Clignotant DROIT désactivé");
    } else {
        activeBlinker = RIGHT;
        isBlinking = true;
        Serial.println("[BLINKER] Clignotant DROIT activé");
    }
}

void LedBlinker::toggleWarningLights() {
    if (activeBlinker == BOTH && isBlinking) {
        stopBlinkers();
        Serial.println("[BLINKER] Warnings désactivés");
    } else {
        activeBlinker = BOTH;
        isBlinking = true;
        Serial.println("[BLINKER] Warnings activés");
    }
}

void LedBlinker::stopBlinkers() {
    activeBlinker = NONE;
    isBlinking = false;
    digitalWrite(leftBlinkerPin, LOW);
    digitalWrite(rightBlinkerPin, LOW);
    Serial.println("[BLINKER] Clignotants désactivés");
}