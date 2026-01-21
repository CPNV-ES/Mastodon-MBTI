#include <Arduino.h>
#include <ESP32Servo.h>

static const int SERVO_PIN = 18;
Servo servo;

// basic parameter
static const int SERVO_CENTER_DEG        = 90;  // centre
static const int SERVO_CENTER_OFFSET_DEG = 6;   // correctif de positionnement 
static const int SERVO_MAX_DEG           = 15;  // ±15° 

static const int ATTACH_MIN_US = 500;
static const int ATTACH_MAX_US = 2500;

static int clampInt(int v, int lo, int hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

// direction: -10..+10  -> angle: (90+offset) ± 15
static int dirToAngleDeg(int direction) {
  direction = clampInt(direction, -10, 10);

  // -10..+10 -> -15..+15
  int delta = (direction * SERVO_MAX_DEG) / 10;

  // centre corrigé
  int center = SERVO_CENTER_DEG + SERVO_CENTER_OFFSET_DEG;

  return center + delta;
}

static void setDirection(int direction) {
  int angle = dirToAngleDeg(direction);
  servo.write(angle);

  Serial.print("Direction = ");
  Serial.print(direction);
  Serial.print("  -> Angle = ");
  Serial.print(angle);
  Serial.println(" deg");
}

void setup() {
  Serial.begin(115200);

  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, ATTACH_MIN_US, ATTACH_MAX_US);

  setDirection(0);
  delay(500);
}

void loop() {
  for (int d = -10; d <= 10; d++) {
    setDirection(d);
    if (d == 0) delay(3000);
    else delay(30);
  }

  for (int d = 10; d >= -10; d--) {
    setDirection(d);
    if (d == 0) delay(3000);
    else delay(30);
  }
}
