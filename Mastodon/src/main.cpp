#include <Arduino.h>

const int TRIG_PIN = 5;  
const int ECHO_PIN = 4;  

const float VITESSE_SON = 0.034; 

void setup() {
  Serial.begin(115200); 
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(1000);
  Serial.println("--- Radar ESP32 Démarré ---");
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duree = pulseIn(ECHO_PIN, HIGH);

  float distance = (duree * VITESSE_SON) / 2;

  Serial.print("Distance : ");
  if (distance == 0 || distance > 400) {
    Serial.println("Hors de portée");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(200); 
}