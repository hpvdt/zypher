void sendUpdate() {
  // Sends update of bike
  String data = String(updateWheelSpeed(), 1);            // Speed
  data = addToString(data, String(updateCadence(), 1));   // Cadence
  data = addToString(data, String(batteryLevel(), 1));    // Battery
  data = addToString(data, String(getTemp(), 1));         // Temp

//  Serial.print(data);
  bluetoothLine.print(data);    // Prints data string
  bluetoothLine.print(('\n'));  // Delimiter character
}

String addToString(String input, String append) {
  // Appends data to a string, using a seperator
  input += ",";
  input += append;
  return (input);
}

void inputRecieved() {
  char input = bluetoothLine.read(); // Read input character
  //Serial.println(input);

  // Due to only head and high being mutually exclusive (since they are the same light) they must turn each other off when turned on
  switch (input) {
    case 'a':
      headOn = LOW;
      break;
    case 'b':
      tailOn = LOW;
      break;
    case 'c':
      leftOn = LOW;
      leftBlinking = false;
      break;
    case 'd':
      rightOn = LOW;
      rightBlinking = false;
      break;
    case 'e':
      highOn = LOW;
      break;
    case 'A':
      headOn = HIGH;
      highOn = LOW;
      break;
    case 'B':
      tailOn = HIGH;
      break;
    case 'C':
      leftOn = HIGH;
      leftBlinking = true;
      changeTime = millis() + halfPeriod;
      break;
    case 'D':
      rightOn = HIGH;
      rightBlinking = true;
      changeTime = millis() + halfPeriod;
      break;
    case 'E':
      highOn = HIGH;
      headOn = LOW;
      break;
    case 'G':
      // Emegency lighting
      emergencyState = true;
      emergencyLight = HIGH;
      break;
    case 'g':
      emergencyState = false;
      break;
    case 'r':
      sendUpdate(); // Update request
      break;
  }

  updateLights();
}
