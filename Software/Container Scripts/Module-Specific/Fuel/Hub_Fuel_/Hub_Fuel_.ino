#include <Wire.h>
#include "definitions.h"

unsigned long lastDebounceTime_b = 0;
unsigned long lastDebounceTime_w = 0;

//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Connect to Simpit
  Wire.begin();
  Serial.begin(115200);


  // Reset Modules
  pinMode(Reset, INPUT);
  delay(100);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);
  delay(1000);

  // Check for Connected Modules
  checkConnections();
}

void loop() {

  // Module Transmissions and Actions
  if ((millis() - lastDebounceTime_w) > 10) {
    transmissions();
    lastDebounceTime_w = millis();
  }
  Serial.println(fuel1);
  delay(100);
}
