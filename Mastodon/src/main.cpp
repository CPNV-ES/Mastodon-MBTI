#include <Arduino.h>
#include "PS4Manager.h"
#include "LedBlinker.h"

const int LED_PIN = 2;           // LED for PS4 controller feedback
const int LED1_PIN = 23;         // Blinker LED 1
const int LED2_PIN = 21;         // Blinker LED 2
const int LED3_PIN = 17;         // Fixed LED 3
const int LED4_PIN = 16;         // Fixed LED 4

const char* PS4_MAC_ADDRESS = "E0:8C:FE:2E:96:6A";

PS4Manager ps4Manager(LED_PIN, 12, 13);
LedBlinker ledBlinker(LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN);

void setup() {
    Serial.begin(115200);
    delay(150);

    ps4Manager.begin(PS4_MAC_ADDRESS);

    ledBlinker.begin();

    ps4Manager.setLedBlinker(&ledBlinker);

    Serial.println("[SETUP] Système initialisé avec succès!");
}

void loop() {

    ps4Manager.update();

    ledBlinker.update();

    delay(10);
}