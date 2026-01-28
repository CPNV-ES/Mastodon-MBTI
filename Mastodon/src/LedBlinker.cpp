#include "LedBlinker.h"

LedBlinker::LedBlinker(int leftPin, int rightPin, int leftPin2, int rightPin2)
    : leftBlinkerPin(leftPin), rightBlinkerPin(rightPin), leftBlinkerPin2(leftPin2), rightBlinkerPin2(rightPin2),
      isBlinking(false), previousMillis(0), ledState(LOW), activeBlinker(NONE) {
}

void LedBlinker::begin() {
    pinMode(leftBlinkerPin, OUTPUT);
    pinMode(rightBlinkerPin, OUTPUT);
    pinMode(leftBlinkerPin2, OUTPUT);
    pinMode(rightBlinkerPin2, OUTPUT);
    
    digitalWrite(leftBlinkerPin, LOW);
    digitalWrite(rightBlinkerPin, LOW);
    digitalWrite(leftBlinkerPin2, LOW);
    digitalWrite(rightBlinkerPin2, LOW);
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
                    digitalWrite(leftBlinkerPin2, ledState);
                    digitalWrite(rightBlinkerPin, LOW);
                    digitalWrite(rightBlinkerPin2, LOW);
                    break;
                    
                case RIGHT:
                    digitalWrite(leftBlinkerPin, LOW);
                    digitalWrite(leftBlinkerPin2, LOW);
                    digitalWrite(rightBlinkerPin, ledState);
                    digitalWrite(rightBlinkerPin2, ledState);
                    break;
                    
                case BOTH:
                    digitalWrite(leftBlinkerPin, ledState);
                    digitalWrite(leftBlinkerPin2, ledState);
                    digitalWrite(rightBlinkerPin, ledState);
                    digitalWrite(rightBlinkerPin2, ledState);
                    break;
                    
                case NONE:
                default:
                    digitalWrite(leftBlinkerPin, LOW);
                    digitalWrite(leftBlinkerPin2, LOW);
                    digitalWrite(rightBlinkerPin, LOW);
                    digitalWrite(rightBlinkerPin2, LOW);
                    break;
            }
        }
    } else {
        digitalWrite(leftBlinkerPin, LOW);
        digitalWrite(leftBlinkerPin2, LOW);
        digitalWrite(rightBlinkerPin, LOW);
        digitalWrite(rightBlinkerPin2, LOW);
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
    digitalWrite(leftBlinkerPin2, LOW);
    digitalWrite(rightBlinkerPin, LOW);
    digitalWrite(rightBlinkerPin2, LOW);
    Serial.println("[BLINKER] Clignotants désactivés");
}