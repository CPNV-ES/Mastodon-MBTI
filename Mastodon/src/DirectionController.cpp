#include "DirectionController.h"

DirectionController::DirectionController(int servoPin) 
    : SERVO_PIN(servoPin), currentDirection(0) {
}

void DirectionController::begin() {
    Serial.println("[DIRECTION] Initialisation du contrôleur de direction...");
    
    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, ATTACH_MIN_US, ATTACH_MAX_US);

    setDirection(0);
    delay(500);
    
    Serial.println("[DIRECTION] Contrôleur de direction initialisé!");
}

int DirectionController::clampInt(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

int DirectionController::dirToAngleDeg(int direction) {
    direction = clampInt(direction, -10, 10);
    
    // -10..+10 -> -15..+15
    int delta = (direction * SERVO_MAX_DEG) / 10;
    
    // Corrected center
    int center = SERVO_CENTER_DEG + SERVO_CENTER_OFFSET_DEG;
    
    return center + delta;
}

void DirectionController::setDirection(int direction) {
    currentDirection = clampInt(direction, -10, 10);
    int angle = dirToAngleDeg(currentDirection);
    servo.write(angle);
    
    Serial.print("[DIRECTION] Direction = ");
    Serial.print(currentDirection);
    Serial.print(" -> Angle = ");
    Serial.print(angle);
    Serial.println("°");
}

void DirectionController::setDirectionFromJoystick(int joystickX) {
    // Joystick X: -128 to 127
    // Apply deadzone
    if (abs(joystickX) < JOYSTICK_DEADZONE) {
        joystickX = 0;
    }
    
    // Map joystick range to direction range
    // -128..127 -> -10..10
    int direction = map(joystickX, -128, 127, -10, 10);
    
    // Only update if direction changed significantly
    if (abs(direction - currentDirection) >= 1) {
        setDirection(direction);
    }
}

int DirectionController::getCurrentDirection() const {
    return currentDirection;
}