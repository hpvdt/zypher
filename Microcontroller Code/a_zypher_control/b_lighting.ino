void updateLights() {
  // Updates light states, note that head and high share line
  if (headOn) {
    analogWrite(headlights, 51); // Only 20% power
  }
  else {
    digitalWrite(highlights, highOn);
  }
  
  digitalWrite(taillights, tailOn);

  if (millis() >= changeTime) { // Switch time
    changeTime = millis() + halfPeriod; // Sets next time
    
    if (rightBlinking) rightOn = !rightOn; // Switches right light
    if (leftBlinking) leftOn = !leftOn; // Switches light
  }
  
  digitalWrite(leftlights, leftOn);
  digitalWrite(rightlights, rightOn);
}
