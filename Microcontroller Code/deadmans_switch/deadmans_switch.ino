const int LED = LED_BUILTIN; // LED to control
const int LEDswitch = 4; // Normal switch
const int deadman = 3; // Deadman's switch
bool LEDstate = true;

void setup() {
  
}

void loop() {
  delay(20); // Rest little controller

  if (digitalRead(deadman) == LOW) {
    // If deadman's switch is released flash at 5Hz
    digitalWrite(LED, LEDstate);
    LEDstate = !(LEDstate);
    delay(100);
  }
  else {
    // Normal operation
    LEDstate = HIGH; // Reset start state (so flashing starts with on)
    digitalWrite(LED, digitalRead(LEDswitch)); // Control LED as normal
  }
}
