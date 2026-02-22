#include <Wire.h>
#include <Keyboard.h>
#include "KerbalSimpit.h"
#include "settings.h"
#include "definitions.h"
#include "actionResults.h"

KerbalSimpit mySimpit(Serial);
unsigned long lastDebounceTime_w = 0;

// Connection-lost detection: if no Simpit message for this long, re-run init().
unsigned long lastSimpitMessageAt = 0;

// Returns true if any button was pressed (emulation mode triggered).
bool checkEmuButton(bool connected, int address, int bytes) {
  if (!connected) return false;
  Wire.requestFrom(address, bytes);
  if (Wire.available() < bytes) {
    while (Wire.available()) Wire.read();
    return false;
  }
  bool anyPressed = false;
  for (int j = 0; j < bytes; j++) {
    if (Wire.read() != 0) anyPressed = true;
  }
  if (anyPressed) {
    keyboardEmulation = true;
    Keyboard.releaseAll();
    return true;
  }
  return false;
}

//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Initialize Modules
  Wire.begin();
  // Connect to Simpit
  Serial.begin(115200);

  // Turn on Keyboard Emulation
  Keyboard.begin();
  delay(1500);
  
  // Reset Modules
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  delay(1000);

  // Check for Connected Modules
  checkConnections();
  allZero();

  // If any connected module has a button pressed during init -> emulation mode
  while (!mySimpit.init()) {
    if (checkEmuButton(Action_Ctrl_Con, Action_Ctrl_, TWO_BYTES)) break;
    if (checkEmuButton(Action2_Ctrl_Con, Action2_Ctrl_, TWO_BYTES)) break;
    if (checkEmuButton(Action3_Ctrl_Con, Action3_Ctrl_, TWO_BYTES)) break;
    if (checkEmuButton(Ctrl_Sys_Ctrl_Con, Ctrl_Sys_Ctrl_, TWO_BYTES)) break;
    if (checkEmuButton(Navigation_Con, Navigation_, ONE_BYTE)) break;
    if (checkEmuButton(Navigation_Time_Ctrl_Con, Navigation_Time_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(Time_Ctrl_Con, Time_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(Stage_Con, Stage_, ONE_BYTE)) break;
    if (checkEmuButton(Abort_Con, Abort_, ONE_BYTE)) break;
    if (checkEmuButton(Executive_Actions_Con, Executive_Actions_, ONE_BYTE)) break;
    if (checkEmuButton(EA_Groups_Ctrl_Con, EA_Groups_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(EA_Control_Ctrl_Con, EA_Control_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(EVA_Ctrl_Con, EVA_Ctrl_, TWO_BYTES)) break;
    if (checkEmuButton(Util_Nav_Ctrl_Con, Util_Nav_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(Util_Time_Ctrl_Con, Util_Time_Ctrl_, ONE_BYTE)) break;
    if (checkEmuButton(Camera_Con, Camera_, TWO_BYTES)) break;
    delay(10);
  }
  
  if (!keyboardEmulation) {
    if (mySimpit.connectedToKSP2()) {
      KSP2 = true;
      Nav_KSP1_KSP2 = KEY_HOME;
    }
    mySimpit.printToKSP(F("Connected to KSP"), PRINT_TO_SCREEN);
    lastSimpitMessageAt = millis();
    // Register Telemetry for LCD
    if (LCD_Con) {
      registerTelemetryChannels();
    }
    // Register Channels
    registerMessageChannels();
  }

  // Setup Analogs
  if (Rotation_Throttle_Con or Translation_Con or Rotation_Con or Analog_Con or Analog_Throttle_Con) {
    analogSetup();
  }
}

void loop() {

  if (!keyboardEmulation) {
    // Get Updates from Simpit
    mySimpit.update();
    // If no message for a while, connection likely lost — re-run init to reconnect
    if (millis() - lastSimpitMessageAt > SIMPIT_CONNECTION_TIMEOUT_MS) {
      Keyboard.releaseAll();
      allZero();
      while (!mySimpit.init()) {delay(10);}
      lastSimpitMessageAt = millis();
      if (LCD_Con) registerTelemetryChannels();
      registerMessageChannels();
    }
  }

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

  if (!keyboardEmulation) {
    // Handle EVA buttons
    if (Translation_Con) {
      if (On_EVA) {
        EVA_Button_LAST = true;
      }
      if (!On_EVA and EVA_Button_LAST) {
        for (int i = 0; i < 11; i++) {
          Keyboard.release(EVA_List_Analog[i]);
        }
        EVA_Button_LAST = false;
      }
    }
    
    // Scene Change
    if (!isFlying) {
      Keyboard.releaseAll();
      allZero();
    }
  }
}
