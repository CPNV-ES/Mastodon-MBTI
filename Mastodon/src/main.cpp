#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

// Define the LED pin
const int LED_PIN = 2;

void setup() {
  // Configure the pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Switch on the LED
  delay(1000);                  // Wait 1 second
  digitalWrite(LED_PIN, LOW);   // Switch off the LED
  delay(1000);                  // Wait 1 second
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}