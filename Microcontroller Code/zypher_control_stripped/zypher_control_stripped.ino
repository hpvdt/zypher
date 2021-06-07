// Pin setup
// Lights
const int headlights = 6;
const int taillights = 5;
const int leftlights = 4;
const int rightlights = 10;
const int highlights = 9;
bool headOn, tailOn, leftOn, rightOn, highOn;

// Other pins
const int battery = A7; // Battery level (from voltage division)

/////////////
// Variables and Constants

// Global variables
bool emergencyState = false; // Records if emergency state is running
bool emergencyLight = HIGH; // Records whether lights are menat to be on or off current flash

// Updates
const unsigned long updatePeriod = 250; // Period (time) between updates (ms)
unsigned long nextUpdate = 0; // Stores time of next update

void setup() {
  Serial.begin(9600); // Bluetooth

  // Lights
  pinMode(headlights, OUTPUT);
  pinMode(taillights, OUTPUT);
  pinMode(leftlights, OUTPUT);
  pinMode(rightlights, OUTPUT);
  pinMode(highlights, OUTPUT);

  digitalWrite(headlights, LOW);
  digitalWrite(taillights, LOW);
  digitalWrite(leftlights, LOW);
  digitalWrite(rightlights, LOW);
  digitalWrite(highlights, LOW);
}

void loop() {
  delay(1); // Rest a little

  while (Serial.available()) {
    inputRecieved();
  }

  // Send update
  if (millis() > nextUpdate) {
    sendUpdate();
    nextUpdate = millis() + updatePeriod; // Sets next update time
  }

  if (emergencyState) {
    digitalWrite(headlights, emergencyLight);
    digitalWrite(taillights, emergencyLight);
    digitalWrite(leftlights, emergencyLight);
    digitalWrite(rightlights, emergencyLight);
    digitalWrite(highlights, emergencyLight);
    emergencyLight = !(emergencyLight); // Flipps light
    delay(500);
  }
}

void sendUpdate() {
  // Sends update of bike
  String data = ""; // String to be sent
  data = addToString(data, "0");     // Speed
  data = addToString(data, "0");        // Cadence
  data = addToString(data, String(batteryLevel(), 1)); // Battery
  data = addToString(data, "0");      // Temp
  // Lights?

  // has to translate characters and send them individually
  data = translate(data);

  for (int x = 0; x < data.length(); x++) {
    byte temp = data.charAt(x);
    Serial.print(temp);
  }
}

String addToString(String input, String append) {
  // Appends data to a string, using a seperator
  input += ",";
  input += append;
  return (input);
}

String translate (String input) {
  // Preps string to be sent over BT by changing characters
  input.replace('3', 'a');
  input.replace('5', 's');
  input.replace('6', 'd');
  input.replace('9', 'b');
  input.replace('0', 'z');
  input.replace('.', 'v');
  input.replace(',', 'u');

  return input;
}

void inputRecieved() {
  char input = Serial.read(); // Read input character

  // Had to adjust command due to a lack of headlights (use highbeams instead)
  switch (input) {
    case 'a': highOn = LOW;
      break;
    case 'b': tailOn = LOW;
      break;
    case 'c': leftOn = LOW;
      break;
    case 'd': rightOn = LOW;
      break;
    case 'e': highOn = LOW;
      break;
    case 'A': highOn = HIGH;
      break;
    case 'B': tailOn = HIGH;
      break;
    case 'C': leftOn = HIGH;
      break;
    case 'D': rightOn = HIGH;
      break;
    case 'E': highOn = HIGH;
      break;
    case 'G':
      // Emegency lighting
      emergencyState = true;
      emergencyLight = HIGH;
      break;
    case 'g': emergencyState = false;
      break;
  }

  updateLights();
}

void updateLights() {
  // Updates light states
  digitalWrite(headlights, headOn);
  digitalWrite(taillights, tailOn);
  digitalWrite(leftlights, leftOn);
  digitalWrite(rightlights, rightOn);
  digitalWrite(highlights, highOn);
}

double batteryLevel() {
  // Returns battery voltage

  // Resistor values in the division
  const double resUpper = 100000.0;
  const double resLower = 10000.0;

  const double scale = (resUpper + resLower) / resLower; // Scaling factor

  double level = 0.0;
  level = 5.0 * analogRead(battery) / 1023; // Record voltage at pin
  level *= scale; // Scales based on division

  return (level);
}
