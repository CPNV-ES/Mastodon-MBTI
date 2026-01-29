#include "AutoModeController.h"
#include "MotorController.h"
#include "DirectionController.h"
#include "UltrasonicController.h"

AutoModeController::AutoModeController(MotorController* motor, DirectionController* direction, UltrasonicController* ultrasonic)
    : motorController(motor), directionController(direction), ultrasonicController(ultrasonic),
      currentState(STOPPED), isAutoModeActive(false), stateStartTime(0) {}

void AutoModeController::begin() {
    Serial.println("[AUTO] AutoMode initialisé");
}

void AutoModeController::toggle() {
    isAutoModeActive = !isAutoModeActive;
    
    if (isAutoModeActive) {
        Serial.println("[AUTO] Mode AUTO activé");
        currentState = FORWARD;
        stateStartTime = millis();
    } else {
        Serial.println("[AUTO] Mode AUTO désactivé");
        currentState = STOPPED;
        motorController->brake();
        directionController->setDirectionFromJoystick(0); 
    }
}

void AutoModeController::update() {
    if (!isAutoModeActive) {
        return;
    }
    
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - stateStartTime;
    
    static unsigned long lastObstacleCheck = 0;
    bool obstacleDetected = false;
    if (currentTime - lastObstacleCheck > 100) {
        obstacleDetected = ultrasonicController->isObstacleDetected(OBSTACLE_THRESHOLD);
        lastObstacleCheck = currentTime;
    }
    
    switch (currentState) {
        case FORWARD:
            motorController->setSpeed(FORWARD_SPEED);
            directionController->setDirectionFromJoystick(0);
            
            if (obstacleDetected) {
                Serial.println("[AUTO] Obstacle détecté ! Passage en REVERSING");
                currentState = REVERSING;
                stateStartTime = currentTime;
            }
            break;
            
        case REVERSING:
            motorController->setSpeed(REVERSE_SPEED);
            directionController->setDirectionFromJoystick(0); 
            
            if (elapsedTime >= REVERSE_DURATION) {
                Serial.println("[AUTO] Fin recul, passage en TURNING");
                currentState = TURNING;
                stateStartTime = currentTime;
            }
            break;
            
        case TURNING:
            motorController->setSpeed(FORWARD_SPEED);
            
            directionController->setDirectionFromJoystick(127);
            
            if (elapsedTime >= TURN_DURATION) {
                Serial.println("[AUTO] Fin virage, retour en FORWARD");
                currentState = FORWARD;
                stateStartTime = currentTime;
                directionController->setDirectionFromJoystick(0);
            }
            break;
            
        case STOPPED:
            motorController->setSpeed(0);
            break;
    }
}

bool AutoModeController::isActive() const {
    return isAutoModeActive;
}