const long timeout = 3000; // ms to 'timeout' and assume bike is stationary

void updateWheelTime() {
  lastWheelMillis = wheelMillis; // Stores old interupt
  wheelMillis = millis(); // Records new interupt time
}
void updateCadenceTime() {
  lastCadenceMillis = cadenceMillis; // Stores old interupt
  cadenceMillis = millis(); // Records new interupt time
}

double batteryLevel() {
  // Returns battery voltage

  // Resistor values in the division
  const double resUpper = 10000.0;
  const double resLower = 5000.0;

  const double scale = (resUpper + resLower) / resLower; // Scaling factor

  double level = 0.0;
  level = 5.0 * analogRead(battery) / 1023; // Record voltage at pin
  level *= scale; // Scales based on division

  return (level);
}

double updateWheelSpeed() {
  if (millis() < (lastWheelMillis + timeout)) {
    // If not timed out yet
    
    wheelSpeed = wheelCirc;
    wheelSpeed /= (wheelMillis - lastWheelMillis); // Calculates speed
    // Note that mm/ms = m/s, hence why the circ is stores in mm
    wheelSpeed *= 3.6; // m/s to km/h
  }
  else {
    // If there hasn't been a rotation in over the timeout period assumes user has stopped
    wheelSpeed = 0;
  }

  return wheelSpeed;
}

double updateCadence() {
  if (millis() < (lastCadenceMillis + timeout)) {
    // Not timed out yet
    cadence = 60000.0 / (cadenceMillis - lastCadenceMillis); // Calculates speed in RPM
  }
  else {
    // If there hasn't been a complete pedal in over the timeout period assumes user has stopped
    cadence = 0;
  }

  return cadence;
}

double getTemp() {
  const double setResis = 9160.0;  // Stores set resistor values
  const double R25 = 100000.0;      // Stores the calibration value of each NTC
  const double T25 = 0.0033557047;  // Stores the reciprical (^-1) of the calibration temperature in K
  const double beta = 3950.0;       // Beta for the thermistors

  double temp, res;                 // Used to store intermediate data and resistance of NTC

  // Find the resistance of the thermistor from voltage division (1023 is Vcc)
  res = (1023.0 / analogRead(tempPin)) - 1;    // Finds ratio of set res to thermistor
  res *= setResis;
  //Serial.println(res);    // Print calculated resistance (used for debugging)

  // Finds temperature
  temp = log(R25 / res);  // Take natural log of R25 over measured resistance
  temp /= beta;                       // Divide by beta
  temp = T25 - temp;                 // Add 1/calibration temp, subtracted previous value
  temp = pow(temp, -1);               // Takes reciprical to get temperature in K
  temp -= 273.15;                      // Kelvin to Celsius

  return temp;
}
