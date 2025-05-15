/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2021 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

#include "HomeSpan.h" 
#include "DEV_active_low_RELAY.h"  // Custom class for relay control with active-low configuration

void setup() {
  // Start serial communication for debugging/logging
  Serial.begin(115200);

  // HomeSpan configuration
  // Set GPIO 12 as control (push-button to start pairing) and GPIO 13 as status LED
  homeSpan.setControlPin(12)  // GPIO pin to enter Setup mode
          .setStatusPin(13)  // GPIO pin for status LED
          .setPairingCode("12345678")  // HomeKit pairing code
          .setHostName("esp32-relay")  // mDNS hostname (e.g., esp32-relay.local)
          .enableOTA("otapassword");  // Enable OTA updates with password

  // Start HomeSpan with accessory category and name
  homeSpan.begin(Category::Bridges, "ESP32 Bridge");
  
  // Define a new accessory (i.e., a logical HomeKit device)
  new SpanAccessory();  // Start accessory definition
  new Service::AccessoryInformation();  // Required service for basic metadata
  new Characteristic::Name("Light Relay");  // Human-readable name
  new Characteristic::Manufacturer("daadaan");  // Manufacturer name
  new Characteristic::Model("Home ESP32 Bridge");  // Device model
  new Characteristic::Identify();  // Used by HomeKit to identify the device (e.g., blink)

  // Add two relays controlled via HomeKit and hardware buttons
  // DEV_RELAY(relayPin, buttonPin)
  new DEV_RELAY(26, 32);  // Relay 1 (active-low) on GPIO 26, controlled by momentary button on GPIO 32
  new DEV_RELAY(27, 33);  // Relay 2 (active-low) on GPIO 27, controlled by momentary button on GPIO 33
}

void loop() {
  // Continually poll HomeSpan for handling HomeKit events and button presses
  homeSpan.poll();
}
