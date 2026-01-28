#include "PS4Manager.h"
#include "LedBlinker.h"
#include "DirectionController.h"
#include "LedController.h"

PS4Manager::PS4Manager(int ledPin, int ledPin1, int ledPin2)
    : LED_PIN(ledPin), LED_PIN_1(ledPin1), LED_PIN_2(ledPin2),
    lastPrint(0), lastBatteryCheck(0), ledBlinker(nullptr), directionController(nullptr), ledController(nullptr),
    lastL1State(false), lastR1State(false), lastTriangleState(false) {
}

void PS4Manager::setLedBlinker(LedBlinker* blinker) {
    ledBlinker = blinker;
}

void PS4Manager::setDirectionController(DirectionController* controller) {
    directionController = controller;
}

void PS4Manager::setLedController(LedController* controller) {
    ledController = controller;
}

void PS4Manager::begin(const char* macAddress) {
    Serial.println("========================================");
    Serial.println("[INFO] Initialisation PS4Controller...");
    PS4.begin(macAddress);
    Serial.println("[INFO] En attente de connexion...");
    Serial.println("========================================");

    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);

    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
}

bool PS4Manager::isConnected() {
    return PS4.isConnected();
}

void PS4Manager::update() {
    if (!PS4.isConnected()) {
        digitalWrite(LED_PIN, LOW);

        static unsigned long lastWait = 0;
        if (millis() - lastWait > 3000) {
            Serial.println("[ATTENTE] En attente de connexion...");
            lastWait = millis();
            for(int i = 0; i < 3; i++) {
            digitalWrite(LED_PIN, HIGH);
            delay(200);
            digitalWrite(LED_PIN, LOW);
            delay(200);
    }
        }
        return;
    }

    handleButtons();
    handleDPad();
    handleJoysticks();
    handleBattery();
}

void PS4Manager::handleButtons() {
    // Face buttons
    if (PS4.Cross()) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("[X] Bouton Croix pressé - LED ON");
        delay(100);
    }

    if (PS4.Circle()) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("[O] Bouton Cercle pressé - LED OFF");
        delay(100);
    }

    bool currentTriangleState = PS4.Triangle();
    if (currentTriangleState && !lastTriangleState) {
        if (ledBlinker != nullptr) {
            ledBlinker->toggleWarningLights();
        }
    }
    lastTriangleState = currentTriangleState;

    if (PS4.Square()) {
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_PIN, HIGH);
            delay(200);
            digitalWrite(LED_PIN, LOW);
            delay(200);
        }
        Serial.println("[□] Bouton Carré pressé - Clignotement lent");
    }
    
    // Shoulder buttons
    bool currentL1State = PS4.L1();
    if (currentL1State && !lastL1State) {
        Serial.println("[L1] Gâchette gauche pressée - Clignotant GAUCHE");
        if (ledBlinker != nullptr) {
            ledBlinker->toggleLeftBlinker();
        }
        PS4.setRumble(50, 0);
        delay(100);
        PS4.setRumble(0, 0);
    }
    lastL1State = currentL1State;

    bool currentR1State = PS4.R1();
    if (currentR1State && !lastR1State) {
        Serial.println("[R1] Gâchette droite pressée - Clignotant DROIT");
        if (ledBlinker != nullptr) {
            ledBlinker->toggleRightBlinker();
        }
        PS4.setRumble(0, 100);
        delay(100);
        PS4.setRumble(0, 0);
    }
    lastR1State = currentR1State;
    
    // Triggers
    if (PS4.L2()) {
        Serial.print("[L2] Trigger gauche: ");
        Serial.println(PS4.L2Value());
        if (ledController != nullptr) {
            ledController->startBrakeLights();
        }
    }
    else {
         if (ledController != nullptr) {
            ledController->stopBrakeLights();
        }
    }
    
    if (PS4.R2()) {
        Serial.print("[R2] Trigger droit: ");
        Serial.println(PS4.R2Value());
    }
    
    // Special buttons
    if (PS4.Share()) {
        Serial.println("[SHARE] Bouton Share pressé");
        delay(200);
    }

    if (PS4.Options()) {
        Serial.println("[OPTIONS] Bouton Options pressé");
        delay(200);
    }

    if (PS4.PSButton()) {
        Serial.println("[PS] Bouton PS pressé");
        delay(200);
    }

    if (PS4.Touchpad()) {
        Serial.println("[TOUCHPAD] Touchpad pressé");
        delay(200);
    }
    
    // Joystick buttons
    if (PS4.L3()) {
        Serial.println("[L3] Joystick gauche cliqué");
        delay(200);
    }

    if (PS4.R3()) {
        Serial.println("[R3] Joystick droit cliqué");
        delay(200);
    }
}

void PS4Manager::handleDPad() {
    if (PS4.Up()) {
        Serial.println("[↑] Haut pressé");
        PS4.setLed(255, 0, 0); // Red
        delay(100);
    }

    if (PS4.Down()) {
        Serial.println("[↓] Bas pressé");
        PS4.setLed(0, 255, 0); // Green
        delay(100);
    }

    if (PS4.Left()) {
        Serial.println("[←] Gauche pressé");
        PS4.setLed(0, 0, 255); // Blue
        delay(100);
    }

    if (PS4.Right()) {
        Serial.println("[→] Droite pressé");
        PS4.setLed(255, 255, 0); // Yellow
        delay(100);
    }
}

void PS4Manager::handleJoysticks() {
    int lx = PS4.LStickX(); // -128 to 127
    int ly = PS4.LStickY(); // -128 to 127
    int rx = PS4.RStickX(); // -128 to 127
    int ry = PS4.RStickY(); // -128 to 127
    
    if (directionController != nullptr) {
        directionController->setDirectionFromJoystick(lx);
    }
    
    if (millis() - lastPrint > PRINT_INTERVAL) {
        if (abs(lx) > 20 || abs(ly) > 20) {
            Serial.print("[JOYSTICK L] X: ");
            Serial.print(lx);
            Serial.print(" Y: ");
            Serial.println(ly);
        }

        if (abs(rx) > 20 || abs(ry) > 20) {
            Serial.print("[JOYSTICK R] X: ");
            Serial.print(rx);
            Serial.print(" Y: ");
            Serial.println(ry);
        }

        lastPrint = millis();
    }
}

void PS4Manager::handleBattery() {
    if (millis() - lastBatteryCheck > BATTERY_CHECK_INTERVAL) {
        Serial.print("[BATTERIE] Niveau: ");
        Serial.print(PS4.Battery());
        Serial.println("%");
        lastBatteryCheck = millis();
    }
}