//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

// Register message channels to Simpit.
void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  if (Action_Ctrl_Con or Action2_Ctrl_Con or Action3_Ctrl_Con or EA_Groups_Ctrl_Con) {mySimpit.registerChannel(CAGSTATUS_MESSAGE);}
  if (Ctrl_Sys_Ctrl_Con or Rotation_Con or Analog_Con or Analog_Throttle_Con or EA_Control_Ctrl_Con) {mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);}
  if (Ctrl_Sys_Ctrl_Con or EA_Control_Ctrl_Con) {mySimpit.registerChannel(SAS_MODE_INFO_MESSAGE);}
  if (EVA_Ctrl_Con || Util_Nav_Ctrl_Con || Util_Time_Ctrl_Con) {mySimpit.registerChannel(EVA_MESSAGE);}
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE);
  mySimpit.registerChannel(SCENE_CHANGE_MESSAGE);
}

// Register telemetry channels to Simpit.
void registerTelemetryChannels() {
  mySimpit.registerChannel(LF_MESSAGE);
  mySimpit.registerChannel(OX_MESSAGE);
  mySimpit.registerChannel(SF_MESSAGE);
  mySimpit.registerChannel(ELECTRIC_MESSAGE);
  mySimpit.registerChannel(XENON_GAS_MESSAGE);
  mySimpit.registerChannel(MONO_MESSAGE);
  mySimpit.registerChannel(APSIDES_MESSAGE);
  mySimpit.registerChannel(APSIDESTIME_MESSAGE);
  mySimpit.registerChannel(ALTITUDE_MESSAGE);
  mySimpit.registerChannel(VELOCITY_MESSAGE);
  mySimpit.registerChannel(DELTAV_MESSAGE);
  mySimpit.registerChannel(ORBIT_MESSAGE);
  mySimpit.registerChannel(MANEUVER_MESSAGE);
}

// Send data to the LCD screen.
void LCD_transmission(int dspl_address, String LCD_data_register[]) {
  if (LCD_transmit == 0) {
      Wire.beginTransmission(dspl_address);
      Wire.write(LCD_transmit);
      sendPacket(LCD_data_register[0]);
      sendPacket(LCD_data_register[1]);
      sendPacket(LCD_data_register[2]);
      Wire.endTransmission();
      LCD_transmit = 1;
  } else if (LCD_transmit == 1) {
      Wire.beginTransmission(dspl_address);
      Wire.write(LCD_transmit);
      sendPacket(LCD_data_register[3]);
      sendPacket(LCD_data_register[4]);
      sendPacket(LCD_data_register[5]);
      Wire.endTransmission();
      LCD_transmit = 2;
  } else if (LCD_transmit == 2) {
      Wire.beginTransmission(dspl_address);
      Wire.write(LCD_transmit);
      sendPacket(LCD_data_register[6]);
      sendPacket(LCD_data_register[7]);
      sendPacket(LCD_data_register[8]);
      sendPacket(LCD_data_register[9]);
      Wire.endTransmission();
      LCD_transmit = 3;
  } else {
      byte LCD_mode_incoming;
      Wire.requestFrom(dspl_address, 1);
      LCD_mode_incoming = Wire.read();
      LCD_transmit = 0;
      if (LCD_mode_incoming != LCD_mode) {
      LCD_mode = LCD_mode_incoming;
      mySimpit.requestMessageOnChannel(0);
      }
  }
}

// Set all LEDs and Screen to blank.
void allZero() {
  if (Ctrl_Sys_Ctrl_Con) {
    Wire.beginTransmission(Ctrl_Sys_Dspl_);
    Wire.write(11);
    Wire.endTransmission();
  }
  if (Action_Ctrl_Con) {
    Wire.beginTransmission(Action_Dspl_);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (Action2_Ctrl_Con) {
    Wire.beginTransmission(Action2_Dspl_);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (EA_Groups_Ctrl_Con) {
    Wire.beginTransmission(EA_Groups_Dspl_);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (EA_Control_Ctrl_Con) {
    Wire.beginTransmission(EA_Control_Dspl_);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (Time_Ctrl_Con) {
    Wire.beginTransmission(Time_Dspl_);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (EVA_Ctrl_Con || Util_Nav_Ctrl_Con || Util_Time_Ctrl_Con) {
    Wire.beginTransmission(EVA_Dspl_);
    Wire.write(0);
    Wire.endTransmission();
  }
  if (LCD_Con) {
    for (int i = 0; i < 10; i++) {
      LCD_data[i] = "X";
    }
    LCD_transmission(LCD_, LCD_data);
    LCD_transmission(LCD_, LCD_data);
    LCD_transmission(LCD_, LCD_data);
    LCD_transmission(LCD_, LCD_data);
  }
}

// Keyboard emulation that presses and releases a key in a single event.
static void tapKey(uint8_t key) {
  Keyboard.press(key);
  delay(10);
  Keyboard.release(key);
} 

// Keyboard emulation functions that consist of a simple press action, like pushing a button.
static void setKey(bool state, uint8_t key, bool &flag) {
  if (state && !flag) {
    Keyboard.press(key);
    flag = true;
  }
  if (!state && flag) {
    Keyboard.release(key);
    flag = false;
  }
}

// Keyboard emulation functions that consist of a press and release action, like a toggle switch.
static void setKey_Switch(bool state, uint8_t key, bool &flag) {
  if (state && !flag) {
    tapKey(key);
    flag = true;
  }
  if (!state && flag) {
    tapKey(key);
    flag = false;
  }
}

// Simpit functions that consist if a simple press action, like pushing a button.
static void setSimpitAction(bool state, byte action, bool &flag, void (*onPress)(byte)) {
  if (state && !flag) {
    onPress(action);
    flag = true;
  }
  if (!state && flag) {
    flag = false;
  }
}

// Simpit functions that require a press and release action, such as for a toggle switch.
static void setSimpitAction_Switch(bool state, byte action, bool &flag, void (*onPress)(byte), void (*onRelease)(byte)) {
  if (state && !flag) {
    onPress(action);
    flag = true;
  }
  if (!state && flag) {
    onRelease(action);
    flag = false;
  }
}

// Keyboard emulation functions for analog joysticks.
static void setAnalogAxisKey(int axisValue, int threshold, bool positiveDir, uint8_t key, bool &flag) {
  if (positiveDir) {
    setKey_Switch(axisValue > threshold, key, flag);
  } else {
    setKey_Switch(axisValue < threshold, key, flag);
  }
}

// Wrapper so setSimpitAction can call activateAction (member functions can't be passed as pointers).
static void simpitActivateAction(byte action) {
  mySimpit.activateAction(action);
}
// Wrapper so setSimpitAction can call deactivateAction (member functions can't be passed as pointers).
static void simpitDeactivateAction(byte action) {
  mySimpit.deactivateAction(action);
}
// Wrapper so setSimpitAction can call toggleAction (member functions can't be passed as pointers).
static void simpitToggleAction(byte action) {
  mySimpit.toggleAction(action);
}
// Wrapper so setSimpitAction can call setSASMode (member functions can't be passed as pointers).
static void simpitSetSASMode(byte action) {
  mySimpit.setSASMode(action);
}
// Helper function to send a timewarp message to Simpit.
static void simpitSendTimewarp(byte) {
  timewarpToMessage TIMEW(TW_type, TW_delay);
  mySimpit.send(TIMEWARP_TO_MESSAGE, TIMEW);
}
// Wrapper so setSimpitAction can call activateCAG (member functions can't be passed as pointers).
static void simpitActivateCAG(byte action) {
  mySimpit.activateCAG(action);
}
// Wrapper so setSimpitAction can call deactivateCAG (member functions can't be passed as pointers).
static void simpitDeactivateCAG(byte action) {
  mySimpit.deactivateCAG(action);
}
// Wrapper so setSimpitAction can call toggleCAG (member functions can't be passed as pointers).
static void simpitToggleCAG(byte action) {
  mySimpit.toggleCAG(action);
}
// Wrapper so setSimpitAction can call cycleNavBallMode (member functions can't be passed as pointers).
static void simpitCycleNavBallMode(byte action) {
  mySimpit.cycleNavBallMode();
}


// Helper function to send a handshake message to a module.
byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

// Check if the modules are connected.
void checkConnections() {
  Action_Ctrl_Con = (sendHandshake(Action_Ctrl_)!=255);
  Action2_Ctrl_Con = (sendHandshake(Action2_Ctrl_)!=255);
  Action3_Ctrl_Con = (sendHandshake(Action3_Ctrl_)!=255);
  Ctrl_Sys_Ctrl_Con = (sendHandshake(Ctrl_Sys_Ctrl_)!=255);
  Navigation_Con = (sendHandshake(Navigation_)!=255);
  Time_Ctrl_Con = (sendHandshake(Time_Ctrl_)!=255);
  Stage_Con = (sendHandshake(Stage_)!=255);
  Abort_Con = (sendHandshake(Abort_)!=255);
  Executive_Actions_Con = (sendHandshake(Executive_Actions_)!=255);
  Rotation_Throttle_Con = (sendHandshake(Rotation_Throttle_)!=255);
  Rotation_Con = (sendHandshake(Rotation_)!=255);
  Translation_Con = (sendHandshake(Translation_)!=255);
  Camera_Con = (sendHandshake(Camera_)!=255);
  EVA_Ctrl_Con = (sendHandshake(EVA_Ctrl_)!=255);
  LCD_Con = (sendHandshake(LCD_)!=255);
  Throttle_Con = (sendHandshake(Throttle_)!=255);
  Navigation_Time_Ctrl_Con = (sendHandshake(Navigation_Time_Ctrl_)!=255);
  EA_Groups_Ctrl_Con = (sendHandshake(EA_Groups_Ctrl_)!=255);
  Analog_Con = (sendHandshake(Analog_)!=255);
  Analog_Throttle_Con = (sendHandshake(Analog_Throttle_)!=255);
  EA_Control_Ctrl_Con = (sendHandshake(EA_Control_Ctrl_)!=255);
  Util_Nav_Ctrl_Con = (sendHandshake(Util_Nav_Ctrl_)!=255);
  Util_Time_Ctrl_Con = (sendHandshake(Util_Time_Ctrl_)!=255);
}

void transmissions() {
  /*
    This function is used to handle the transmissions to and from the modules.
    It takes the control address, the control array, the number of input bytes,
    the display address, the display array, and the number of output bytes.
    It then sends the control array to the control address and the display array
    to the display address.

    ctrl_address, ctrl[], in_bytes, dspl_address, dspl[], out_bytes
  */
  
}

// Handle actions in response to changes detected by modules.
void actions() {
  
}
