#include <PS4Controller.h>

const int LED_PIN = 2;

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

unsigned long lastPrint = 0;
const int PRINT_INTERVAL = 100; // ms

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  pinMode(LED_PIN, OUTPUT);
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  Serial.println("========================================");
  Serial.println("[INFO] Initialisation PS4Controller...");
  PS4.begin("E0:8C:FE:2E:96:6A");
  
  Serial.println("[INFO] En attente de connexion...");
  Serial.println("========================================");
}

void loop() {
  if (PS4.isConnected()) {
    
    if (PS4.Cross()) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("[X] Bouton Croix pressé - LED ON");
      delay(100);
    }
    
    if (PS4.Circle()) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("[O] Bouton Cercle pressé - LED OFF");
      delay(100);
    }
    
    if (PS4.Triangle()) {
      for(int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(50);
        digitalWrite(LED_PIN, LOW);
        delay(50);
      }
      Serial.println("[△] Triangle pressé - Clignotement rapide");
    }
    
    if (PS4.Square()) {
      for(int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
      }
      Serial.println("[□] Carré pressé - Clignotement lent");
    }
    
    if (PS4.L1()) {
      Serial.println("[L1] Gâchette gauche pressée");
      PS4.setRumble(50, 0);
      delay(100);
      PS4.setRumble(0, 0);
    }
    
    if (PS4.R1()) {
      Serial.println("[R1] Gâchette droite pressée");
      PS4.setRumble(0, 100);
      delay(100);
      PS4.setRumble(0, 0);
    }
    
    if (PS4.L2()) {
      Serial.print("[L2] Trigger gauche: ");
      Serial.println(PS4.L2Value()); 
    }
    
    if (PS4.R2()) {
      Serial.print("[R2] Trigger droit: ");
      Serial.println(PS4.R2Value());
    }
    
    if (PS4.Up()) {
      Serial.println("[↑] Haut pressé");
      PS4.setLed(255, 0, 0); // Red
      delay(100);
    }
    
    if (PS4.Down()) {
      Serial.println("[↓] Bas pressé");
      PS4.setLed(0, 255, 0); // Green
      delay(100);
    }
    
    if (PS4.Left()) {
      Serial.println("[←] Gauche pressé");
      PS4.setLed(0, 0, 255); // Blue
      delay(100);
    }
    
    if (PS4.Right()) {
      Serial.println("[→] Droite pressé");
      PS4.setLed(255, 255, 0); // Yellow
      delay(100);
    }
    
    if (PS4.Share()) {
      Serial.println("[SHARE] Bouton Share pressé");
      delay(200);
    }
    
    if (PS4.Options()) {
      Serial.println("[OPTIONS] Bouton Options pressé");
      delay(200);
    }
    
    if (PS4.PSButton()) {
      Serial.println("[PS] Bouton PS pressé");
      delay(200);
    }
    
    if (PS4.Touchpad()) {
      Serial.println("[TOUCHPAD] Touchpad pressé");
      delay(200);
    }
    
    if (PS4.L3()) {
      Serial.println("[L3] Joystick gauche cliqué");
      delay(200);
    }
    
    if (PS4.R3()) {
      Serial.println("[R3] Joystick droit cliqué");
      delay(200);
    }
    
    if (millis() - lastPrint > PRINT_INTERVAL) {
      
      int lx = PS4.LStickX(); // -128 to 127
      int ly = PS4.LStickY(); // -128 to 127
      int rx = PS4.RStickX(); // -128 to 127
      int ry = PS4.RStickY(); // -128 to 127
      
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
    
    static unsigned long lastBatteryCheck = 0;
    if (millis() - lastBatteryCheck > 10000) {
      Serial.print("[BATTERIE] Niveau: ");
      Serial.print(PS4.Battery());
      Serial.println("%");
      lastBatteryCheck = millis();
    }
    
  } else {
    digitalWrite(LED_PIN, LOW);
    
    static unsigned long lastWait = 0;
    if (millis() - lastWait > 3000) {
      Serial.println("[ATTENTE] En attente de connexion...");
      lastWait = millis();
    }
  }
  
  delay(10); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);


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
