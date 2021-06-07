#include <SoftwareSerial.h>
SoftwareSerial SerialBLE(3, 2); // RX, TX

void setup() {
  // Setup serial stream for bluetooth and the computer
  SerialBLE.begin(9600);
  Serial.begin(9600);
}

void loop() {
  delay(1);
  if (Serial.available()) {
    String text = Serial.readString();
    text = translate(text);
    
    for (int x = 0; x < text.length(); x++) {
      byte temp = text.charAt(x);
      SerialBLE.write(temp);
      Serial.print(temp);
    }
    Serial.print('\n');
  }

  if (SerialBLE.available()) {
    Serial.println(SerialBLE.readString());
  }
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
