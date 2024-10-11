#include <Wire.h>
#include <Joystick.h>
#include <Keyboard.h>
#include "definitions.h"
#include "settings.h"
#include "actionResults.h"

unsigned long lastDebounceTime_b = 0;
unsigned long lastDebounceTime_w = 0;
unsigned long lastDebounceTime_d = 0;

Joystick_ Joystick1(0xAF, JOYSTICK_TYPE_JOYSTICK, 7);

//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Initialize Modules
  Wire.begin();

  // Reset Modules
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  delay(1000);

  // Check for Connected Modules
  checkConnections();
  allZero();
  Joystick1.begin();
  Keyboard.begin();
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Module Transmissions and Actions
  if (((millis() - lastDebounceTime_w) > update_time) and (isFlying)) {
    if (Rotation_Throttle_Con or Rotation_Con) {
      readRotation();
    }
    if (Translation_Con) {
      readTranslation();
    }
    if (Throttle_Con) {
      readThrottle();
    }
    if (Analog_Throttle_Con or Analog_Con) {
      readAnalog();
    }
    actions();
    transmissions();
    Joystick1.sendState();
    lastDebounceTime_w = millis();
  }
}
