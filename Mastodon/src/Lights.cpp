#include "Lights.h"

Lights::Lights(int brakePin, int fixedPin, int r1, int g1, int b1)
    : brakeLightPin(brakePin), fixedLedPin(fixedPin),
      rgbRedPin1(r1), rgbGreenPin1(g1), rgbBluePin1(b1),
      isBrakeOn(false) {}

void Lights::begin() {
    pinMode(brakeLightPin, OUTPUT);
    pinMode(fixedLedPin, OUTPUT);
    pinMode(rgbRedPin1, OUTPUT);
    pinMode(rgbGreenPin1, OUTPUT);
    pinMode(rgbBluePin1, OUTPUT);

    digitalWrite(brakeLightPin, LOW);
    digitalWrite(fixedLedPin, HIGH);

    digitalWrite(rgbRedPin1, HIGH);
    digitalWrite(rgbGreenPin1, HIGH);
    digitalWrite(rgbBluePin1, HIGH);
}

void Lights::startBrakeLights() {
    digitalWrite(brakeLightPin, HIGH);
    isBrakeOn = true;
}

void Lights::stopBrakeLights() {
    digitalWrite(brakeLightPin, LOW);
    isBrakeOn = false;
}

bool Lights::getBrakeLightsState() const {
    return isBrakeOn;
}