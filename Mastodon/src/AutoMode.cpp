#include "AutoMode.h"
#include "Motor.h"
#include "Steering.h"
#include "Ultrasonic.h"

AutoMode::AutoMode(Motor* motorCtrl, Steering* steeringCtrl, Ultrasonic* ultrasonicCtrl)
    : motor(motorCtrl), steering(steeringCtrl), ultrasonic(ultrasonicCtrl),
      currentState(STOPPED), isAutoModeActive(false), stateStartTime(0) {}

void AutoMode::begin() {
    Serial.println("[AUTO] AutoMode initialized");
}

void AutoMode::toggle() {
    isAutoModeActive = !isAutoModeActive;

    if (isAutoModeActive) {
        Serial.println("[AUTO] AUTO mode ON");
        currentState = FORWARD;
        stateStartTime = millis();
    } else {
        Serial.println("[AUTO] AUTO mode OFF");
        currentState = STOPPED;
        motor->brake();
        steering->setDirectionFromJoystick(0);
    }
}

void AutoMode::update() {
    if (!isAutoModeActive) {
        return;
    }

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - stateStartTime;

    static unsigned long lastObstacleCheck = 0;
    bool obstacleDetected = false;
    if (currentTime - lastObstacleCheck > 100) {
        obstacleDetected = ultrasonic->isObstacleDetected(OBSTACLE_THRESHOLD);
        lastObstacleCheck = currentTime;
    }

    switch (currentState) {
        case FORWARD:
            motor->setSpeed(FORWARD_SPEED);
            steering->setDirectionFromJoystick(0);

            if (obstacleDetected) {
                Serial.println("[AUTO] Obstacle detected! Switching to REVERSING");
                currentState = REVERSING;
                stateStartTime = currentTime;
            }
            break;

        case REVERSING:
            motor->setSpeed(REVERSE_SPEED);
            steering->setDirectionFromJoystick(0);

            if (elapsedTime >= REVERSE_DURATION) {
                Serial.println("[AUTO] Reverse complete, switching to TURNING");
                currentState = TURNING;
                stateStartTime = currentTime;
            }
            break;

        case TURNING:
            motor->setSpeed(FORWARD_SPEED);

            steering->setDirectionFromJoystick(127);

            if (elapsedTime >= TURN_DURATION) {
                Serial.println("[AUTO] Turn complete, returning to FORWARD");
                currentState = FORWARD;
                stateStartTime = currentTime;
                steering->setDirectionFromJoystick(0);
            }
            break;

        case STOPPED:
            motor->setSpeed(0);
            break;
    }
}

bool AutoMode::isActive() const {
    return isAutoModeActive;
}