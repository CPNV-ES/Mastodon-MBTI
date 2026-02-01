#include "RemoteControl.h"
#include "Blinkers.h"
#include "Steering.h"
#include "Lights.h"
#include "Motor.h"
#include "AutoMode.h"

RemoteControl::RemoteControl(int ledPin, int ledPin1, int ledPin2)
    : LED_PIN(ledPin), LED_PIN_1(ledPin1), LED_PIN_2(ledPin2),
    lastPrint(0), lastBatteryCheck(0), blinkers(nullptr), steering(nullptr), lights(nullptr), motor(nullptr), autoMode(nullptr),
    obstacleDetected(false), lastL1State(false), lastR1State(false), lastTriangleState(false), lastOptionsState(false) {
}

void RemoteControl::setBlinkers(Blinkers* blinker) {
    blinkers = blinker;
}

void RemoteControl::setSteering(Steering* controller) {
    steering = controller;
}

void RemoteControl::setLights(Lights* controller) {
    lights = controller;
}

void RemoteControl::setMotor(Motor* controller) {
    motor = controller;
}

void RemoteControl::setAutoMode(AutoMode* controller) {
    autoMode = controller;
}

void RemoteControl::setObstacleDetected(bool detected) {
    obstacleDetected = detected;
}

void RemoteControl::begin(const char* macAddress) {
    Serial.println("========================================");
    Serial.println("[INFO] Initializing PS4 controller...");
    PS4.begin(macAddress);
    Serial.println("[INFO] Waiting for connection...");
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

bool RemoteControl::isConnected() {
    return PS4.isConnected();
}

void RemoteControl::update() {
    if (!PS4.isConnected()) {
        digitalWrite(LED_PIN, LOW);

        static unsigned long lastWait = 0;
        if (millis() - lastWait > 3000) {
            Serial.println("[WAITING] Waiting for connection...");
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

void RemoteControl::handleButtons() {
    bool isAutoActive = (autoMode != nullptr && autoMode->isActive());

    // Face buttons
    if (PS4.Cross()) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("[X] Cross button pressed - LED ON");
    }

    if (PS4.Circle()) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("[O] Circle button pressed - LED OFF");
    }

    bool currentTriangleState = PS4.Triangle();
    if (currentTriangleState && !lastTriangleState) {
        if (blinkers != nullptr) {
            blinkers->toggleWarningLights();
        }
    }
    lastTriangleState = currentTriangleState;

    if (PS4.Square()) {
        Serial.println("[□] Square button pressed");
    }

    // Shoulder buttons
    bool currentL1State = PS4.L1();
    if (currentL1State && !lastL1State) {
        Serial.println("[L1] Left trigger pressed - LEFT blinker");
        if (blinkers != nullptr) {
            blinkers->toggleLeftBlinker();
        }
        PS4.setRumble(50, 0);
        PS4.setRumble(0, 0);
    }
    lastL1State = currentL1State;

    bool currentR1State = PS4.R1();
    if (currentR1State && !lastR1State) {
        Serial.println("[R1] Right trigger pressed - RIGHT blinker");
        if (blinkers != nullptr) {
            blinkers->toggleRightBlinker();
        }
        PS4.setRumble(0, 100);
        PS4.setRumble(0, 0);
    }
    lastR1State = currentR1State;

    if (!isAutoActive) {
        bool l2Pressed = PS4.L2();
        bool r2Pressed = PS4.R2();

        if (l2Pressed) {
            int l2Value = PS4.L2Value(); // 0-255

            if (motor != nullptr) {
                int reverseSpeed = -l2Value;
                motor->setSpeed(reverseSpeed);

                if (lights != nullptr) {
                    lights->startBrakeLights();
                }
            }
        }
        else if (r2Pressed) {
            int throttleValue = PS4.R2Value(); // 0-255

            if (obstacleDetected && throttleValue > 0) {
                Serial.println("[MOTOR] Acceleration blocked - Obstacle detected!");
                motor->setSpeed(0);
            } else {
                if (motor != nullptr) {
                    motor->setSpeed(throttleValue);
                }
            }

            if (lights != nullptr) {
                lights->stopBrakeLights();
            }
        }
        else {
            if (motor != nullptr) {
                motor->setSpeed(0);
            }

            if (lights != nullptr) {
                lights->stopBrakeLights();
            }
        }
    }

    // Special buttons
    if (PS4.Share()) {
        Serial.println("[SHARE] Share button pressed");
    }

    bool currentOptionsState = PS4.Options();
    if (currentOptionsState && !lastOptionsState) {
        Serial.println("[OPTIONS] Toggle AUTO Mode");
        if (autoMode != nullptr) {
            autoMode->toggle();
        }
    }
    lastOptionsState = currentOptionsState;

    if (PS4.PSButton()) {
        Serial.println("[PS] PS button pressed");
    }

    if (PS4.Touchpad()) {
        Serial.println("[TOUCHPAD] Touchpad pressed");
    }

    // Joystick buttons
    if (PS4.L3()) {
        Serial.println("[L3] Left joystick clicked");
    }

    if (PS4.R3()) {
        Serial.println("[R3] Right joystick clicked");
    }
}

void RemoteControl::handleDPad() {
    if (PS4.Up()) {
        Serial.println("[↑] Up pressed");
        PS4.setLed(255, 0, 0); // Red
    }

    if (PS4.Down()) {
        Serial.println("[↓] Down pressed");
        PS4.setLed(0, 255, 0); // Green
    }

    if (PS4.Left()) {
        Serial.println("[←] Left pressed");
        PS4.setLed(0, 0, 255); // Blue
    }

    if (PS4.Right()) {
        Serial.println("[→] Right pressed");
        PS4.setLed(255, 255, 0); // Yellow
    }
}

void RemoteControl::handleJoysticks() {
    int lx = PS4.LStickX(); // -128 to 127
    int ly = PS4.LStickY(); // -128 to 127
    int rx = PS4.RStickX(); // -128 to 127
    int ry = PS4.RStickY(); // -128 to 127

    if (steering != nullptr) {
        steering->setDirectionFromJoystick(lx);
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

void RemoteControl::handleBattery() {
    if (millis() - lastBatteryCheck > BATTERY_CHECK_INTERVAL) {
        Serial.print("[BATTERY] Level: ");
        Serial.print(PS4.Battery());
        Serial.println("%");
        lastBatteryCheck = millis();
    }
}