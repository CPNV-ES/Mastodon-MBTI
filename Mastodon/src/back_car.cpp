/*
 * CAPTEUR DE DISTANCE POUR VOITURE LEGO
 */


const int TRIG_PIN = 16;
const int ECHO_PIN = 17;

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("Capteur pret!");
  Serial.println("");
}

//MESURER LA DISTANCE
float mesurer_distance() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Mesurer le temps de retour
  long duree = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Calculer la distance
  float distance = (duree * 0.0343) / 2;
  
  
  if (distance == 0 || distance > 400) {
    return -1;
  }
  
  return distance;
}


void loop() {
  float distance = mesurer_distance();
  
  if (distance < 0) {
    Serial.println("Erreur de lecture");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");
  }
  
  delay(200);  
}
```


```
Distance: 25.3 cm
Distance: 24.8 cm
Distance: 23.5 cm
Distance: 15.2 cm
Distance: 8.7 cm