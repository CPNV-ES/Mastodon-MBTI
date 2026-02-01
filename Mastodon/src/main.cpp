#include <Arduino.h>
#include "RemoteControl.h"
#include "Blinkers.h"
#include "Steering.h"
#include "Lights.h"
#include "Ultrasonic.h"
#include "Motor.h"
#include "AutoMode.h"

// Pin definitions
const int PS4_FEEDBACK_LED_PIN = 2;
const int LEFT_BLINKER_PIN = 23;
const int RIGHT_BLINKER_PIN = 21;
const int LEFT_BLINKER_PIN_2 = 19;
const int RIGHT_BLINKER_PIN_2 = 22;
const int BRAKE_LIGHT_PIN = 17;
const int FIXED_LED_PIN = 16;
const int SERVO_PIN = 18;
const int RGB1_RED_PIN = 25;
const int RGB1_GREEN_PIN = 26;
const int RGB1_BLUE_PIN = 27;
const int ULTRASONIC_TRIG_PIN = 5;
const int ULTRASONIC_ECHO_PIN = 4;
const int MOTOR_PIN1 = 12;
const int MOTOR_PIN2 = 13;
const int MOTOR_ENABLE_PIN = 15;

// Configuration
const char* PS4_MAC_ADDRESS = "E0:8C:FE:2E:96:6A"; // PS4 controller MAC address
const float MANUAL_MODE_OBSTACLE_THRESHOLD = 20.0; // cm
const unsigned long OBSTACLE_CHECK_INTERVAL = 200; // ms

// Component instances
RemoteControl remoteControl(PS4_FEEDBACK_LED_PIN, 16, 17);
Blinkers blinkers(LEFT_BLINKER_PIN, RIGHT_BLINKER_PIN, LEFT_BLINKER_PIN_2, RIGHT_BLINKER_PIN_2);
Steering steering(SERVO_PIN);
Lights lights(BRAKE_LIGHT_PIN, FIXED_LED_PIN, RGB1_RED_PIN, RGB1_GREEN_PIN, RGB1_BLUE_PIN);
Ultrasonic ultrasonic(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN);
Motor motor(MOTOR_PIN1, MOTOR_PIN2, MOTOR_ENABLE_PIN);
AutoMode autoMode(&motor, &steering, &ultrasonic);

void setup() {
    Serial.begin(115200);
    delay(150);

    remoteControl.begin(PS4_MAC_ADDRESS);

    steering.begin();
    lights.begin();
    blinkers.begin();
    ultrasonic.begin();
    motor.begin();
    autoMode.begin();

    remoteControl.setSteering(&steering);
    remoteControl.setBlinkers(&blinkers);
    remoteControl.setLights(&lights);
    remoteControl.setMotor(&motor);
    remoteControl.setAutoMode(&autoMode);
    motor.setBlinkers(&blinkers);

    Serial.println("[SETUP] System initialized successfully!");
}

void loop() {
    remoteControl.update();
    blinkers.update();
    autoMode.update();

    static unsigned long lastUltrasonicCheck = 0;
    static bool obstacleAhead = false;

    if (!autoMode.isActive() && millis() - lastUltrasonicCheck > OBSTACLE_CHECK_INTERVAL) {
        obstacleAhead = ultrasonic.isObstacleDetected(MANUAL_MODE_OBSTACLE_THRESHOLD);

        remoteControl.setObstacleDetected(obstacleAhead);

        if (obstacleAhead) {
            motor.emergencyStop();
            lights.startBrakeLights();
        } else {
            lights.stopBrakeLights();
        }
        
        lastUltrasonicCheck = millis();
    }
    
    delay(10);
}