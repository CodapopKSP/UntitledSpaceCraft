#include <Wire.h>
#include "KerbalSimpit.h"
#include "definitions.h"
#include "settings.h"
#include "actionResults.h"

KerbalSimpit mySimpit(Serial);
unsigned long lastDebounceTime_b = 0;
unsigned long lastDebounceTime_w = 0;
unsigned long lastDebounceTime_d = 0;

// Turn on Keyboard Emulation
keyboardEmulatorMessage KEY(0x00);
keyboardEmulatorMessage KEY_mod(0x00, 0);

//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Initialize Modules
  Wire.begin();
  // Connect to Simpit
  Serial.begin(115200);
  
  // Reset Modules
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  delay(1000);

  // Check for Connected Modules
  checkConnections();
  allZero();

  while (!mySimpit.init()) {delay(100);}
  if (mySimpit.connectedToKSP2()) {
    KSP2 = true;
    Nav_List[0] = 0x24;
  }

  
  mySimpit.printToKSP(F("Connected to KSP"), PRINT_TO_SCREEN);

  // Setup Analogs
  if (Rotation_Throttle_Con or Translation_Con or Rotation_Con or Analog_Con or Analog_Throttle_Con) {
    analogSetup();
  }

  // Register Channels
  registerMessageChannels();

  // Register Telemetry for LCD
  if (LCD_Con) {
    registerTelemetryChannels();
  }
}

void loop() {
  // Get Updates from Simpit
  mySimpit.update();
  //mySimpit.printToKSP(String(mySimpit.packetDroppedNbr));

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
    transmissions();
    actions();
    lastDebounceTime_w = millis();
  }

  // Handle EVA buttons
  if (Translation_Con) {
    if (On_EVA) {
      EVA_Button_LAST = true;
    }
    if (!On_EVA and EVA_Button_LAST) {
      if (shift_is_down or ctrl_is_down or w_is_down or a_is_down or s_is_down or d_is_down or f_is_down or b_is_down or space_is_down) {
        EVA_is_down = true;
      }
    }
    if (EVA_is_down) {
      KEY.modifier = KEY_UP_MOD;
      for (int i = 0; i < 11; i++) {
        KEY.keyCode = EVA_List_Analog[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
      KEY.modifier = 0;
      EVA_is_down = false;
    }
  }
  
  // Scene Change
  if (!isFlying) {
    allZero();
  }
}
