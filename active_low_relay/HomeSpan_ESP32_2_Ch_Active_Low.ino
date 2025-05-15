#include "HomeSpan.h" 
#include "DEV_active_low_RELAY.h"  // Custom class for relay control with active-low configuration

void setup() {
  // Start serial communication for debugging/logging
  Serial.begin(115200);

  // HomeSpan configuration
  // Set GPIO 12 as control (push-button to start pairing) and GPIO 13 as status LED
  homeSpan.setControlPin(12)
          .setStatusPin(13)
          .setPairingCode("12345678")  // HomeKit pairing code
          .begin(Category::Bridges, "ESP32 Bridge");  // Start HomeSpan in "Bridge" category

  // Define a new accessory (i.e., a logical HomeKit device)
  new SpanAccessory();  // Start accessory definition
  new Service::AccessoryInformation();  // Required service for basic metadata
  new Characteristic::Name("Light Relay");  // Human-readable name
  new Characteristic::Manufacturer("daadaan");  // Manufacturer name
  new Characteristic::Model("Home ESP32 Bridge");  // Device model
  new Characteristic::Identify();  // Used by HomeKit to identify the device (e.g., blink)

  // Add two relays controlled via HomeKit and hardware buttons
  // DEV_RELAY(relayPin, buttonPin)
  new DEV_RELAY(26, 32);  // Relay 1 on GPIO 26, controlled by momentary button on GPIO 32
  new DEV_RELAY(27, 33);  // Relay 2 on GPIO 27, controlled by momentary button on GPIO 33
}

void loop() {
  // Continually poll HomeSpan for handling HomeKit events and button presses
  homeSpan.poll();
}
