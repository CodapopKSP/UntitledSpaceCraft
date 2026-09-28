#include <Wire.h>
#include "KerbalSimpit.h"
#include "definitions.h"
#include "actionResults.h"

KerbalSimpit mySimpit(Serial);
unsigned long lastDebounceTime_b = 0;
unsigned long lastDebounceTime_w = 0;

// Turn on Keyboard Emulation
keyboardEmulatorMessage KEY(0x00);
keyboardEmulatorMessage KEY_mod(0x00, 0);
timewarpMessage TIMEW;

//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Connect to Simpit
  Wire.begin();
  Serial.begin(115200);
  while (!mySimpit.init()) {delay(100);}
  mySimpit.printToKSP("Connected", PRINT_TO_SCREEN);

  // Register Channels
  analogSetup();

  // Reset Modules
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  delay(1000);

  // Check for Connected Modules
  checkConnections();
}

void loop() {
  // Get Updates from Simpit
  mySimpit.update();

  // Module Transmissions and Actions
  if ((millis() - lastDebounceTime_w) > 10) {
    readAnalogs();
    transmissions();
    actions();
    lastDebounceTime_w = millis();
  }
}
