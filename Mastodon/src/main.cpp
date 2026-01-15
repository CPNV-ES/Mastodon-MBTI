#include <Arduino.h>


const int led1 = 23; 
const int led2 = 21; 
const int led3 = 17; 
const int led4 = 16; 
const int buttonPin = 18;


bool isBlinking = false;    
int lastButtonState = HIGH; 


unsigned long buttonPressedTime = 0;
const long longPressDuration = 2000; 
bool isPressing = false;


unsigned long previousMillis = 0;
const long interval = 300; 
bool ledState = HIGH;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}

void loop() {
  int reading = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  // 1. GESTION DU BOUTON
  if (reading == LOW && lastButtonState == HIGH) {
    // On vient d'appuyer
    buttonPressedTime = currentMillis;
    isPressing = true;
  }

  if (isPressing && reading == LOW) {
    // Si on maintient l'appui plus de 2 secondes : ON ARRÊTE
    if (isBlinking && (currentMillis - buttonPressedTime >= longPressDuration)) {
      isBlinking = false;
      isPressing = false; 
      digitalWrite(led1, HIGH); // On les remet fixes
      digitalWrite(led2, HIGH);
    }
  }

  if (reading == HIGH && lastButtonState == LOW) {
    // On vient de relâcher le bouton
    // Si c'était un appui court : ON ACTIVE
    if (!isBlinking && (currentMillis - buttonPressedTime < longPressDuration)) {
      isBlinking = true;
    }
    isPressing = false;
    delay(50); // Anti-rebond
  }
  lastButtonState = reading;

  // 2. GESTION DU CLIGNOTEMENT (LED 1 et 2)
  if (isBlinking) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led1, ledState);
      digitalWrite(led2, ledState);
    }
  } else {
    // Si on ne clignote pas, elles doivent être allumées
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }

  // 3. LEDS FIXES (LED 3 et 4)
  // Elles restent allumées quoi qu'il arrive
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}