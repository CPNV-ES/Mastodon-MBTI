<Arduino.h>
 
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
 
// ===== NOUVEAU : SYSTÈME DE WARNING =====

bool warningMode = false;

unsigned long warningPreviousMillis = 0;

const long warningInterval = 150; // Clignotement plus rapide pour le warning

bool warningLedState = LOW;

int warningClickCount = 0;

unsigned long lastWarningClick = 0;

const long warningClickWindow = 1000; // Fenêtre de 1 seconde pour 3 clics
 
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

    // Détection de triple clic pour activer/désactiver le mode warning

    if (currentMillis - lastWarningClick < warningClickWindow) {

      warningClickCount++;

      if (warningClickCount >= 2) { // 3 clics au total (0, 1, 2)

        warningMode = !warningMode;

        warningClickCount = 0;

        if (!warningMode) {

          // Restaurer l'état normal

          digitalWrite(led3, HIGH);

          digitalWrite(led4, HIGH);

        }

      }

    } else {

      warningClickCount = 0;

    }

    lastWarningClick = currentMillis;

  }
 
  if (isPressing && reading == LOW) {

    // Si on maintient l'appui plus de 2 secondes : ON ARRÊTE

    if (isBlinking && (currentMillis - buttonPressedTime >= longPressDuration)) {

      isBlinking = false;

      isPressing = false; 

      digitalWrite(led1, HIGH);

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

    digitalWrite(led1, HIGH);

    digitalWrite(led2, HIGH);

  }
 
  // 3. GESTION DES WARNINGS (LED 3 et 4)

  if (warningMode) {

    // Clignotement rapide pour le warning

    if (currentMillis - warningPreviousMillis >= warningInterval) {

      warningPreviousMillis = currentMillis;

      warningLedState = !warningLedState;

      digitalWrite(led3, warningLedState);

      digitalWrite(led4, warningLedState);

    }

  } else {

    // Mode normal : LEDs fixes

    digitalWrite(led3, HIGH);

    digitalWrite(led4, HIGH);

  }

}
 