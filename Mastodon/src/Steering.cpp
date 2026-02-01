#include "Steering.h"

Steering::Steering(int servoPin)
    : SERVO_PIN(servoPin), currentDirection(0) {
}

void Steering::begin() {
    Serial.println("[STEERING] Initializing steering controller...");

    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, ATTACH_MIN_US, ATTACH_MAX_US);

    setDirection(0);
    delay(500);

    Serial.println("[STEERING] Steering controller initialized!");
}

int Steering::clampInt(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

int Steering::dirToAngleDeg(int direction) {
    direction = clampInt(direction, -10, 10);

    // -10..+10 -> -15..+15
    int delta = (direction * SERVO_MAX_DEG) / 10;

    // Corrected center
    int center = SERVO_CENTER_DEG + SERVO_CENTER_OFFSET_DEG;

    return center + delta;
}

void Steering::setDirection(int direction) {
    currentDirection = clampInt(direction, -10, 10);
    int angle = dirToAngleDeg(currentDirection);
    servo.write(angle);

    Serial.print("[STEERING] Direction = ");
    Serial.print(currentDirection);
    Serial.print(" -> Angle = ");
    Serial.print(angle);
    Serial.println("°");
}

void Steering::setDirectionFromJoystick(int joystickX) {
    // Joystick X: -128 to 127
    // Apply deadzone
    if (abs(joystickX) < JOYSTICK_DEADZONE) {
        joystickX = 0;
    }

    // Map joystick range to direction range (inverted)
    // -128..127 -> 10..-10 (inverted to match wheel direction)
    int direction = map(joystickX, -128, 127, 10, -10);

    // Only update if direction changed significantly
    if (abs(direction - currentDirection) >= 1) {
        setDirection(direction);
    }
}

int Steering::getCurrentDirection() const {
    return currentDirection;
}