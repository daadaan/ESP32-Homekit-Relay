# ESP32-Homekit-Relay
A HomeKit-enabled ESP32 project to control relays with physical buttons using HomeSpan.

## Features

- HomeKit-compatible via HomeSpan
- Momentary button toggles each relay (on/off)
- State retained in HomeKit
- GPIO-safe pin selection for ESP32 DevKit v1

## Hardware Connections

| Component  | GPIO |
|------------|------|
| Relay 1    | 26   |
| Button 1   | 32   |
| Relay 2    | 27   |
| Button 2   | 33   |
| Status LED | 13   |
| Control Pin| 12   |

The following is the wiring diagram:

![ESP32 Wokwi](https://github.com/user-attachments/assets/dd19c8d2-2d7c-4e04-ab78-17ca54e3c441)

## References and Sources
- @HomeSpan for ESP32 HomeKit firmware [GitHub link](https://github.com/HomeSpan/HomeSpan)
- @Wokwi for the wiring diagram [website](https://wokwi.com/)
