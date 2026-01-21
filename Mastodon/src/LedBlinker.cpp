#include "LedBlinker.h"

LedBlinker::LedBlinker(int led1Pin, int led2Pin, int led3Pin, int led4Pin, int btnPin)
    : led1(led1Pin), led2(led2Pin), led3(led3Pin), led4(led4Pin), buttonPin(btnPin),
      isBlinking(false), lastButtonState(HIGH), buttonPressedTime(0), 
      isPressing(false), previousMillis(0), ledState(HIGH), activeBlinker(NONE) {
}

void LedBlinker::begin() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    
    pinMode(buttonPin, INPUT_PULLUP);
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
}

void LedBlinker::update() {
    handleButton();
    updateLeds();
}

void LedBlinker::handleButton() {
    int reading = digitalRead(buttonPin);
    unsigned long currentMillis = millis();
    
    if (reading == LOW && lastButtonState == HIGH) {
        buttonPressedTime = currentMillis;
        isPressing = true;
    }
    
    if (isPressing && reading == LOW) {
        if (isBlinking && (currentMillis - buttonPressedTime >= longPressDuration)) {
            isBlinking = false;
            isPressing = false;
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
        }
    }
    
    if (reading == HIGH && lastButtonState == LOW) {
        if (!isBlinking && (currentMillis - buttonPressedTime < longPressDuration)) {
            activeBlinker = BOTH;
            isBlinking = true;
        }
        isPressing = false;
        delay(50);
    }
    
    lastButtonState = reading;
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
    
    digitalWrite(led3, HIGH);
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