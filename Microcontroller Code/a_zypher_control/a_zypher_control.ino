
#define bluetoothLine Serial
// Used to switch between serial lines when troubleshooting

// Pin setup
// Lights
const int headlights = 9; // Note: this is currently the same as high
const int taillights = 5;
const int leftlights = 16; // A2
const int rightlights = 10;
const int highlights = 9;
bool headOn, tailOn, leftOn, rightOn, highOn;
bool leftBlinking, rightBlinking; // Used to record if they are blinking
unsigned long changeTime; // Used to record when the next blink should occur
unsigned int halfPeriod = 500; // Recorded period between state changes for lights (ms)

// Modules
const int SD_CS = 4; // SD card chip select
const int NF_enable = 7; // NF24 enable pin
const int NF_CS = 8; // NF24 chip select

// Hall effects (A3144 models are used)
// Assuming cadence is on hall2 signal
const int cadenceAnalog = 15;
const int cadenceDigital = 2;
// Assuming wheel is on hall 1 signal
const int wheelAnalog = 16;
const int wheelDigital = 3;

// Other pins
const int tempPin = A3; // Temperature pin
const int battery = A7; // Battery level (from voltage division)

/////////////
// Variables and Constants

// Constants
const double wheelCirc = 2070.0;  // Wheel circumference (mm, for quicker calculations)

// Global variables
double wheelSpeed = 0; // Stores wheel speed (km/h)
volatile unsigned long lastWheelMillis = 0; // Stores last step when wheel was tripped
volatile unsigned long wheelMillis = 1000; // Stores step when wheel was tripped

double cadence = 0; // Stores cadence (RPM)
volatile unsigned long lastCadenceMillis = 0; // Stores last step when cadence was tripped
volatile unsigned long cadenceMillis = 1000; // Stores step when cadence was tripped
bool emergencyState = false; // Records if emergency state is running
bool emergencyLight = HIGH; // Records whether lights are menat to be on or off current flash

void setup() {
  bluetoothLine.begin(9600); // Bluetooth
  
  // Lights
  pinMode(headlights, OUTPUT);
  pinMode(taillights, OUTPUT);
  pinMode(leftlights, OUTPUT);
  pinMode(rightlights, OUTPUT);
  pinMode(highlights, OUTPUT);

  // Interrupts for hall effect sensors
  pinMode(wheelDigital,INPUT_PULLUP); // A3144 works by pulling down its output pin in the presence of a field 
  attachInterrupt(digitalPinToInterrupt(wheelDigital), updateWheelTime, FALLING); // Hall interupt
  pinMode(cadenceDigital,INPUT_PULLUP); // A3144 works by pulling down its output pin in the presence of a field 
  attachInterrupt(digitalPinToInterrupt(cadenceDigital), updateCadenceTime, FALLING); // Hall interupt
}

void loop() {
  delay(1); // Rest a little

  while (bluetoothLine.available()) {
    inputRecieved();
  }
  
  if (emergencyState) {
    digitalWrite(headlights, emergencyLight);
    digitalWrite(taillights, emergencyLight);
    digitalWrite(leftlights, emergencyLight);
    digitalWrite(rightlights, emergencyLight);
    digitalWrite(highlights, emergencyLight);
    emergencyLight = !(emergencyLight); // Flips light
    delay(500);
  }
  updateLights();
}
