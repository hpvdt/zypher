#include <Wire.h>
#include <SD.h>
#include <SPI.h>

bool sdSetup(const int sd_pin) {
  // Sets up SD card, returns true if everything's alright

  pinMode(sd_pin, OUTPUT);
  return (SD.begin(sd_pin));  // Record presence
}
