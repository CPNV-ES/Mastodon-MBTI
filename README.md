# 🦣 Mastodon-MBTI Project

> ESP32-based LEGO robotics car controlled via PS4 controller with autonomous navigation capabilities

---

## 📹 Project Demo

Watch our project presentation:

[![Mastodon Demo Video](https://img.youtube.com/vi/JzLjOKZWoG4/maxresdefault.jpg)](https://youtu.be/JzLjOKZWoG4)

> *Click the image above to watch the full demonstration*

---

## 💻 Installation

### Prerequisites

- [PlatformIO](https://platformio.org/) (recommended)
- USB cable for ESP32 programming
- PS4 controller

### Setup Instructions

1. **Clone the repository**
```bash
   git clone <repository-url>
   cd mastodon-mbti
```

2. **Install dependencies**
   
   PlatformIO will automatically install required libraries:
   - `PS4Controller` by aed3
   - `ESP32Servo`

3. **Configure PS4 Controller MAC Address**
   
   Use SixaxisPairTool to pair your PS4 controller with the ESP32's Bluetooth MAC address.
   
   Update in `src/main.cpp`:
```cpp
   const char* PS4_MAC_ADDRESS = "YOUR:ESP32:BLUETOOTH:MAC";
```
4. **Build and Upload**
   
   Using PlatformIO:
```bash
   pio run --target upload
```
   
   Or use the PlatformIO GUI in VS Code.

5. **Monitor Serial Output**
```bash
   pio device monitor
```

---

## 🔧 Hardware

### Pin Configuration
```cpp
// Motor Control
#define MOTOR_PIN1          12
#define MOTOR_PIN2          13
#define MOTOR_ENABLE_PIN    15

// Steering
#define SERVO_PIN           18

// Sensors
#define ULTRASONIC_TRIG_PIN 5
#define ULTRASONIC_ECHO_PIN 4

// Lighting
#define BRAKE_LIGHT_PIN     17
#define FIXED_LED_PIN       16
#define LEFT_BLINKER_PIN    23
#define RIGHT_BLINKER_PIN   21
#define LEFT_BLINKER_PIN_2  19
#define RIGHT_BLINKER_PIN_2 22

// RGB LED
#define RGB1_RED_PIN        25
#define RGB1_GREEN_PIN      26
#define RGB1_BLUE_PIN       27

// PS4 Feedback
#define PS4_FEEDBACK_LED_PIN 2
```

---

## 🏗️ Software Architecture

### Class Structure

| Class | Responsibility | Key Methods |
|-------|---------------|-------------|
| `RemoteControl` | PS4 controller management | `begin()`, `update()`, `handleButtons()` |
| `Motor` | DC motor speed control | `setSpeed()`, `brake()`, `emergencyStop()` |
| `Steering` | Servo-based direction | `setDirection()`, `setDirectionFromJoystick()` |
| `Blinkers` | Turn signal management | `toggleLeftBlinker()`, `toggleRightBlinker()` |
| `Lights` | Brake/headlight control | `startBrakeLights()`, `stopBrakeLights()` |
| `Ultrasonic` | Distance measurement | `getDistance()`, `isObstacleDetected()` |
| `AutoMode` | Autonomous navigation | `toggle()`, `update()` |

---

## 🎮 Usage

### PS4 Controller Mapping

#### Manual Mode

| Button/Trigger | Function |
|----------------|----------|
| **R2** (Right Trigger) | Throttle (forward) |
| **L2** (Left Trigger) | Reverse |
| **Left Joystick (X-axis)** | Steering |
| **L1** | Toggle left turn signal |
| **R1** | Toggle right turn signal |
| **Triangle** | Toggle warning lights |
| **Cross (X)** | Turn on feedback LED |
| **Circle (O)** | Turn off feedback LED |
| **OPTIONS** | Toggle autonomous mode |

#### Autonomous Mode

When activated with **OPTIONS** button:
- Robot drives forward automatically
- Detects obstacles with ultrasonic sensor
- Reverses when obstacle < 20cm
- Turns to avoid obstacle
- Returns to forward motion

---

## 📚 Documentation

### Project Documents

- 📊 [Project Pitch Presentation](docs/Pitch.pptx) - 3-minute overview
- 📝 [Work Logs](docs/worklogs) - Detailed development timeline
- 📋 [Technical Report](docs/Report_Project_Mastodon-MBTI.docx) - In-depth technical analysis

---

## 👥 Team

**Project Members:**
- **Maximilian Lopizzo** - maximilian.lopizzo@eduvaud.ch
- **Bryan Zweiacker** - bryan.zweiacker@eduvaud.ch
- **Ilyass Chelli** - ilyass.chelli@eduvaud.ch
- **Trystan Gaillard** - trystan.gaillard@eduvaud.ch

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
