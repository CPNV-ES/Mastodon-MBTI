#include "LedBlinker.h"

LedBlinker::LedBlinker(int led1Pin, int led2Pin, int led4Pin)
    : led1(led1Pin), led2(led2Pin), led4(led4Pin),
      isBlinking(false), previousMillis(0), ledState(HIGH), activeBlinker(NONE) {
}

void LedBlinker::begin() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led4, OUTPUT);
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led4, HIGH);
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
                    digitalWrite(led1, ledState);
                    digitalWrite(led2, HIGH);
                    break;
                    
                case RIGHT:
                    digitalWrite(led1, HIGH);
                    digitalWrite(led2, ledState);
                    break;
                    
                case BOTH:
                    digitalWrite(led1, ledState);
                    digitalWrite(led2, ledState);
                    break;
                    
                case NONE:
                default:
                    digitalWrite(led1, HIGH);
                    digitalWrite(led2, HIGH);
                    break;
            }
        }
    } else {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
    }
    
    digitalWrite(led4, HIGH);
}

void LedBlinker::startLeftBlinker() {
    activeBlinker = LEFT;
    isBlinking = true;
    Serial.println("[BLINKER] Clignotant GAUCHE activé");
}

void LedBlinker::startRightBlinker() {
    activeBlinker = RIGHT;
    isBlinking = true;
    Serial.println("[BLINKER] Clignotant DROIT activé");
}

void LedBlinker::stopBlinkers() {
    activeBlinker = NONE;
    isBlinking = false;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    Serial.println("[BLINKER] Clignotants désactivés");
}