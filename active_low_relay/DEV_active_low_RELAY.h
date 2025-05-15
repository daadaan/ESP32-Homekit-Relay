// Custom Relay Accessory with Momentary Button Control (Active-Low Relay)

struct DEV_RELAY : Service::LightBulb {

  int relayPin;                // GPIO pin connected to relay (active-low)
  int switchPin;               // GPIO pin connected to momentary push button
  SpanCharacteristic *power;  // HomeKit characteristic for On/Off state

  // Constructor: Initializes the relay and sets up the button
  DEV_RELAY(int pin, int switchPin) : Service::LightBulb() {

    power = new Characteristic::On();  // Create HomeKit On/Off characteristic

    new SpanButton(switchPin);         // Create button handler for this GPIO

    this->switchPin = switchPin;       // Store button GPIO pin
    this->relayPin = pin;              // Store relay GPIO pin

    pinMode(relayPin, OUTPUT);         // Configure relay pin as output

    // Set initial state of relay based on HomeKit state (inverted for active-low)
    digitalWrite(relayPin, !power->getVal());
  }

  // HomeKit update handler: called when user toggles from Home app
  boolean update() {
    // Write inverse of HomeKit value (LOW = ON for active-low relays)
    digitalWrite(relayPin, !power->getNewVal());
    return true;
  }

  // Physical button handler: toggles relay on single press
  void button(int pin, int pressType) override {
    if (pin == switchPin) {
      if (pressType == SpanButton::SINGLE) {
        bool ChangeSwitchToState = !power->getVal();  // Toggle state
        power->setVal(ChangeSwitchToState);           // Update HomeKit state
        digitalWrite(relayPin, !ChangeSwitchToState); // Update relay state (active-low)
      }
    }
  }
};
