#include <Arduino.h>
#include "PS4Manager.h"
#include "LedBlinker.h"
#include "DirectionController.h"
#include "LedController.h"

const int PS4_FEEDBACK_LED_PIN = 2;
const int LEFT_BLINKER_PIN = 23;
const int RIGHT_BLINKER_PIN = 21;
const int LEFT_BLINKER_PIN_2 = 19;
const int RIGHT_BLINKER_PIN_2 = 22;
const int BRAKE_LIGHT_PIN = 17;
const int FIXED_LED_PIN = 16;
const int SERVO_PIN = 18;
const int RGB1_RED_PIN = 25;
const int RGB1_GREEN_PIN = 26;
const int RGB1_BLUE_PIN = 27;

const char* PS4_MAC_ADDRESS = "E0:8C:FE:2E:96:6A";

PS4Manager ps4Manager(PS4_FEEDBACK_LED_PIN, 16, 17);
LedBlinker ledBlinker(LEFT_BLINKER_PIN, RIGHT_BLINKER_PIN, LEFT_BLINKER_PIN_2, RIGHT_BLINKER_PIN_2);
DirectionController directionController(SERVO_PIN);
LedController ledController(BRAKE_LIGHT_PIN, FIXED_LED_PIN, 
                            RGB1_RED_PIN, RGB1_GREEN_PIN, RGB1_BLUE_PIN);

void setup() {
    Serial.begin(115200);
    delay(150);

    ps4Manager.begin(PS4_MAC_ADDRESS);

    directionController.begin();
    ledController.begin();
    ledBlinker.begin();

    ps4Manager.setDirectionController(&directionController);
    ps4Manager.setLedBlinker(&ledBlinker);
    ps4Manager.setLedController(&ledController);

    Serial.println("[SETUP] Système initialisé avec succès!");
}

void loop() {
    ps4Manager.update();
    ledBlinker.update();
    
    delay(10);
}