void setup() {
  Serial.begin(9600);
  Serial3.begin(38400);
}

void loop() {
  if (Serial3.available() > 0) {
    char temp = Serial3.read();
    Serial.print("Recieved: ");
    Serial.println(temp);

    if (temp == 'r') {
      Serial3.write(temp);
      
      byte x = 0;
      Serial.print("Sent: ");
      Serial.print(x);
      Serial3.write(x);

      //      Serial3.write(int(highByte(x)));
      //      Serial.print(int(highByte(x)));
      //      Serial3.write(int(lowByte(x)));
      //      Serial.print(int(lowByte(x)));
      Serial3.write(byte('\n'));
      Serial.println();
    }
  }
  if (Serial.available() > 0) {
    Serial.print("Sent: ");
    String temp = Serial.readString();
    Serial.print(temp);

    for (int i = 0; i < temp.length(); i++) {
      Serial3.write(temp.charAt(i));
    }
  }
}
