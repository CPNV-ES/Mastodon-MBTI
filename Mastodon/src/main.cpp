#include <Arduino.h>
#include <ESP32Servo.h>
#include "PS4Manager.h"
#include "LedBlinker.h"

const int LED_PIN = 2;           // LED for PS4 controller feedback
const int LED1_PIN = 23;         // Blinker LED 1
const int LED2_PIN = 21;         // Blinker LED 2
const int LED3_PIN = 17;         // Fixed LED 3
const int LED4_PIN = 16;         // Fixed LED 4
static const int SERVO_PIN = 18;

const char* PS4_MAC_ADDRESS = "E0:8C:FE:2E:96:6A";

Servo servo;
PS4Manager ps4Controller(LED_PIN);
LedBlinker ledBlinker(LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN);

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

  delay(150);
  
  ps4Controller.begin(PS4_MAC_ADDRESS);
  
  ledBlinker.begin();
  
  ps4Controller.setLedBlinker(&ledBlinker);
  
  Serial.println("[SETUP] Système initialisé avec succès!");

  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, ATTACH_MIN_US, ATTACH_MAX_US);

  setDirection(0);
  delay(500);
}

void loop() {

  ps4Controller.update();
  
  ledBlinker.update();
  
  delay(10);

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
