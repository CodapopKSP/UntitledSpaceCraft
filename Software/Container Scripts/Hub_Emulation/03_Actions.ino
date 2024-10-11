//|-------------------|
//|      Actions      |
//|-------------------|

void Action_Action() {
  int Action_combinedBytes = Action_Ctrl[0] + (Action_Ctrl[1]*256);
  if (Action_combinedBytes != Action_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Action_combinedBytes != Action_STATE) {
    Action_STATE = Action_combinedBytes;
    for (int i = 0; i < 10; i++) {
      button_keypress((Action_STATE & 1<<i), Action_Group_Emu[i], Action_Group_Bool[i]);
    }
  }
  Action_LAST = Action_STATE;
}

void Action2_Action() {
  int Action2_combinedBytes = Action2_Ctrl[0] + (Action2_Ctrl[1]*256);
  if (Action2_combinedBytes != Action2_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Action2_combinedBytes != Action2_STATE) {
    Action2_STATE = Action2_combinedBytes;
    for (int i = 0; i < 10; i++) {
      button_keypress((Action2_STATE & 1<<i), Action_Group2_Emu[i], Action_Group2_Bool[i]);
    }
  }
  Action2_LAST = Action2_STATE;
}

void Action3_Action() {
  int Action3_combinedBytes = Action3_Ctrl[0] + (Action3_Ctrl[1]*256);
  if (Action3_combinedBytes != Action3_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Action3_combinedBytes != Action3_STATE) {
    Action3_STATE = Action3_combinedBytes;
    for (int i = 0; i < 10; i++) {
      button_keypress((Action3_STATE & 1<<i), Action_Group3_Emu[i], Action_Group3_Bool[i]);
    }
  }
  Action2_LAST = Action2_STATE;
}

void Ctrl_Sys_Action() {
  ControlSys_combinedBytes = Ctrl_Sys_Ctrl[0] + (Ctrl_Sys_Ctrl[1]*256);
  if (ControlSys_combinedBytes != Ctrl_Sys_LAST) {
    lastDebounceTime_b = millis();
  }
  if (ControlSys_combinedBytes != Ctrl_Sys_STATE) {
    Ctrl_Sys_STATE = ControlSys_combinedBytes;
    for (int i = 0; i < 10; i++) {
      button_keypress((Ctrl_Sys_STATE & 1<<i), Control_Systems_Emu[i], Control_Systems_Bool[i]);
    }
    // SAS/RCS
    switch_keytoggle(ControlSys_combinedBytes & 1024, Control_Systems_Emu[10], Control_Systems_Bool[10]);
    switch_keytoggle(ControlSys_combinedBytes & 2048, Control_Systems_Emu[11], Control_Systems_Bool[11]);
  }
  Ctrl_Sys_LAST = Ctrl_Sys_STATE;
}

void Navigation_Action() {
  if (Navigation[0] != Navigation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation[0] != Navigation_STATE) {
    Navigation_STATE = Navigation[0];
    switch_keytoggle(Navigation_STATE & 1, Navigation_Emu[0], Navigation_Bool[11]);
    for (int i = 1; i < 4; i++) {
      button_keypress((Navigation_STATE & 1<<i), Navigation_Emu[i], Navigation_Bool[i]);
    }
    switch_keytoggle(Navigation_STATE & 1<<4, Navigation_Emu[4], Navigation_Bool[4]);
    for (int i = 5; i < 8; i++) {
      button_keypress((Navigation_STATE & 1<<i), Navigation_Emu[i], Navigation_Bool[i]);
    }
  }
  Navigation_LAST = Navigation_STATE;
}

void Time_Action() {
  if (Time_Ctrl[0] != Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Time_Ctrl[0] != Time_STATE) {
    Time_STATE = Time_Ctrl[0];
    button_keypress((Time_STATE & 1<<0), Time_Emu[0], Time_Bool[0]);
    button_keypress((Time_STATE & 1<<1), Time_Emu[1], Time_Bool[1]);
    button_keypress((Time_STATE & 1<<2), Time_Emu[2], Time_Bool[2]);
    button_keypress((Time_STATE & 1<<3), Time_Emu[3], Time_Bool[3]);
    button_keypress((Time_STATE & 1<<4), Time_Emu[4], Time_Bool[4]);
    button_keypress((Time_STATE & 1<<5), Time_Emu[5], Time_Bool[5]);
    button_keypress((Time_STATE & 1<<6), Time_Emu[6], Time_Bool[6]);
    button_keypress((Time_STATE & 1<<7), Time_Emu[7], Time_Bool[7]);
  }
  Time_LAST = Time_STATE;
}

void Stage_Action() {
  if (Stage_Con or Abort_Con) {
    byte abort_byte = 0;
    if (abortB[0] & 1) {
      abort_byte = 2;
    }
    Stage_Abort[0] = stageB[0] + abort_byte;
  }
  // Stage Button
  if (Stage_Abort[0] != Stage_Abort_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Stage_Abort[0] != Stage_Abort_STATE) {
    Stage_Abort_STATE = Stage_Abort[0];
    button_keypress((Stage_Abort_STATE & 1), Executive_Actions_Emu[0], Executive_Actions_Bool[0]);
    button_keypress((Stage_Abort_STATE & 2), Executive_Actions_Emu[1], Executive_Actions_Bool[1]);
  }
  Stage_Abort_LAST = Stage_Abort_STATE;
}

void Translation_Action() {
  if (Translation[0] != Translation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Translation[0] != Translation_STATE) {
    Translation_STATE = Translation[0];
    button_keypress((Translation_STATE & 1<<0), Analog_Emu[10], Translation_Bool[0]);
    switch_keytoggle((Translation_STATE & 1<<1), Analog_Emu[12], Translation_Bool[1]);
    switch_keytoggle((Translation_STATE & 1<<2), Analog_Emu[2], Translation_Bool[2]);
    button_keypress(Translation_STATE & 1<<3, Analog_Emu[3], Translation_Bool[3]);
    button_keypress(Translation_STATE & 1<<4, Analog_Emu[11], Translation_Bool[4]);
  }
  Translation_LAST = Translation_STATE;

  // Execute
  if (Enable_Joystick_Keyboard_Emulation) {
    button_keypress((Translation_axis0 > 600), Joystick_Keyboard_Emu[6], Joystick_Keyboard_Bool[6]);
    button_keypress((Translation_axis1 > 600), Joystick_Keyboard_Emu[7], Joystick_Keyboard_Bool[7]);
    button_keypress((Translation_axis2 > 600), Joystick_Keyboard_Emu[8], Joystick_Keyboard_Bool[8]);
    button_keypress((Translation_axis0 < 400), Joystick_Keyboard_Emu[9], Joystick_Keyboard_Bool[9]);
    button_keypress((Translation_axis1 < 400), Joystick_Keyboard_Emu[10], Joystick_Keyboard_Bool[10]);
    button_keypress((Translation_axis2 < 400), Joystick_Keyboard_Emu[11], Joystick_Keyboard_Bool[11]);
  } else {
    Joystick1.setRxAxis(Translation_axis0);
    Joystick1.setRyAxis(Translation_axis1);
    Joystick1.setRzAxis(Translation_axis2);
  }
}

void Rotation_Action() {

  if (Rotation[0] != Rotation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Rotation[0] != Rotation_STATE) {
    Rotation_STATE = Rotation[0];
    button_keypress(Rotation_STATE & 1<<0, Analog_Emu[0], Analog_And_Rotation_Bool[0]);
    button_keypress(Rotation_STATE & 1<<3, Analog_Emu[1], Analog_And_Rotation_Bool[3]);
    switch_keytoggle(Rotation_STATE & 1<<2, Analog_Emu[6], Analog_And_Rotation_Bool[2]);
    switch_keytoggle(Rotation_STATE & 1<<1, Analog_Emu[7], Analog_And_Rotation_Bool[1]);
    switch_keytoggle(Rotation_STATE & 1<<4, Analog_Emu[4], Analog_And_Rotation_Bool[4]);
    button_keypress(Rotation_STATE & 1<<5, Analog_Emu[5], Analog_And_Rotation_Bool[5]);
  }
  Rotation_LAST = Rotation_STATE;

  // Execute
  if (Enable_Joystick_Keyboard_Emulation) {
    button_keypress((Rotation_axis1 > 600), Joystick_Keyboard_Emu[0], Joystick_Keyboard_Bool[0]);
    button_keypress((Rotation_axis2 > 600), Joystick_Keyboard_Emu[1], Joystick_Keyboard_Bool[1]);
    button_keypress((Rotation_axis0 > 600), Joystick_Keyboard_Emu[2], Joystick_Keyboard_Bool[2]);
    button_keypress((Rotation_axis1 < 400), Joystick_Keyboard_Emu[3], Joystick_Keyboard_Bool[3]);
    button_keypress((Rotation_axis2 < 400), Joystick_Keyboard_Emu[4], Joystick_Keyboard_Bool[4]);
    button_keypress((Rotation_axis0 < 400), Joystick_Keyboard_Emu[5], Joystick_Keyboard_Bool[5]);
    if (Rotation_Throttle_Con) {
      button_keypress((Rotation_throttle > 400), Joystick_Keyboard_Emu[12], Joystick_Keyboard_Bool[12]);
    }
  } else {
    Joystick1.setXAxis(Rotation_axis1);
    Joystick1.setYAxis(Rotation_axis2);
    Joystick1.setZAxis(Rotation_axis0);
    if (Rotation_Throttle_Con) {
      Joystick1.setThrottle(Rotation_throttle);
    }
  }
}

void Camera_Action() {
  Camera_combinedBytes = Camera[0] + (Camera[1]*256);
  if (Camera_combinedBytes != Camera_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Camera_combinedBytes != Camera_STATE) {
    Camera_STATE = Camera_combinedBytes;

    for (int i = 0; i < 8; i++) {
      button_keypress((Camera_STATE & 1<<i), Camera_Emu[i], Camera_Bool[i]);
    }
  }
  Camera_LAST = Camera_STATE;
}

void EVA_Action() {
  EVA_combinedBytes = (EVA_Ctrl[1]*256) + EVA_Ctrl[0];
  if (EVA_combinedBytes != EVA_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EVA_combinedBytes != EVA_STATE) {
    EVA_STATE = EVA_combinedBytes;

    for (int i = 0; i < 11; i++) {
      button_keypress((EVA_STATE & 1<<i), EVA_Emu[i], EVA_Bool[i]);
    }
  }
  EVA_LAST = EVA_STATE;
}

void Throttle_Action() {
  for (int i = 0; i < 2; i++) {
    button_keypress((Throttle[0] & 1<<i), Throttle_Emu[i], Throttle_Bool[i]);
  }

  // Execute
  if (Enable_Joystick_Keyboard_Emulation) {
    button_keypress((throttle > 10000), Joystick_Keyboard_Emu[12], Joystick_Keyboard_Bool[12]);
  } else {
    Joystick1.setThrottle(throttle);
  }
}

void Navigation_Time_Action() {
  if (Navigation_Time_Ctrl[0] != Navigation_Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation_Time_Ctrl[0] != Navigation_Time_STATE) {
    Navigation_Time_STATE = Navigation_Time_Ctrl[0];

    for (int i = 0; i < 7; i++) {
      button_keypress((Navigation_Time_STATE & 1<<i), Navigation_Emu[i], Navigation_Bool[i]);
    }
    switch_keytoggle(Navigation_Time_STATE & 128, Navigation_Emu[3], Navigation_Bool[3]);
  }
  Navigation_Time_LAST = Navigation_Time_STATE;
}

void EA_Groups_Action() {
  int EA_Groups_combinedBytes = EA_Groups_Ctrl[0];
  if (EA_Groups_combinedBytes != EA_Groups_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EA_Groups_combinedBytes != EA_Groups_STATE) {
    EA_Groups_STATE = EA_Groups_combinedBytes;
    for (int i = 0; i < 5; i++) {
      button_keypress((EA_Groups_STATE & 1<<i), Executive_Actions_Emu[i], Executive_Actions_Bool[i]);
    }
  }
  EA_Groups_LAST = EA_Groups_STATE;
}

void Analog_Action() {

  if (Analog_Con) {
    if (Analog[0] != Analog_LAST) {
      lastDebounceTime_b = millis();
    }
    if (Analog[0] != Analog_STATE) {
      Analog_STATE = Analog[0];
      button_keypress((Analog_STATE & 1<<0), Analog_Emu[0], Analog_And_Rotation_Bool[0]);
      button_keypress((Analog_STATE & 1<<1), Analog_Emu[1], Analog_And_Rotation_Bool[1]);
      switch_keytoggle(Analog_STATE & 1<<6, Analog_Emu[4], Analog_And_Rotation_Bool[4]);
      button_keypress(Analog_STATE & 1<<2, Analog_Emu[2], Analog_And_Rotation_Bool[2]);
      switch_keytoggle(Analog_STATE & 1<<3, Analog_Emu[7], Analog_And_Rotation_Bool[7]);
      switch_keytoggle(Analog_STATE & 1<<4, Analog_Emu[6], Analog_And_Rotation_Bool[6]);
      switch_keytoggle(Analog_STATE & 1<<5, Analog_Emu[9], Analog_And_Rotation_Bool[9]);
    }
    Analog_LAST = Analog_STATE;
  }

  // Execute
  if (Enable_Joystick_Keyboard_Emulation) {
    button_keypress((Analog_axis1 > 600), Joystick_Keyboard_Emu[0], Joystick_Keyboard_Bool[0]);
    button_keypress((Analog_axis2 > 600), Joystick_Keyboard_Emu[1], Joystick_Keyboard_Bool[1]);
    button_keypress((Analog_axis0 > 600), Joystick_Keyboard_Emu[2], Joystick_Keyboard_Bool[2]);
    button_keypress((Analog_axis1 < 400), Joystick_Keyboard_Emu[3], Joystick_Keyboard_Bool[3]);
    button_keypress((Analog_axis2 < 400), Joystick_Keyboard_Emu[4], Joystick_Keyboard_Bool[4]);
    button_keypress((Analog_axis0 < 400), Joystick_Keyboard_Emu[5], Joystick_Keyboard_Bool[5]);
    if (Analog_Throttle_Con) {
      button_keypress((Rotation_throttle > 400), Joystick_Keyboard_Emu[12], Joystick_Keyboard_Bool[12]);
    }
  } else {
    Joystick1.setXAxis(Analog_axis1);
    Joystick1.setYAxis(Analog_axis2);
    Joystick1.setZAxis(Analog_axis0);
    if (Analog_Throttle_Con) {
      Joystick1.setThrottle(Rotation_throttle);
    }
  }
}

void EA_Control_Action() {
  if (EA_Control_Ctrl[0] != EA_Control_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EA_Control_Ctrl[0] != EA_Control_STATE) {
    EA_Control_STATE = EA_Control_Ctrl[0];
    
    button_keypress((EA_Control_STATE & 1<<0), Executive_Actions_Emu[7], Executive_Actions_Bool[7]);
    button_keypress((EA_Control_STATE & 1<<1), Executive_Actions_Emu[8], Executive_Actions_Bool[8]);
    button_keypress((EA_Control_STATE & 1<<2), Executive_Actions_Emu[9], Executive_Actions_Bool[9]);
    switch_keytoggle((EA_Control_STATE & 1<<3), Executive_Actions_Emu[10], Executive_Actions_Bool[10]);
    switch_keytoggle((EA_Control_STATE & 1<<4), Executive_Actions_Emu[11], Executive_Actions_Bool[11]);
    button_keypress((EA_Control_STATE & 1<<5), Executive_Actions_Emu[0], Executive_Actions_Bool[0]);
    button_keypress((EA_Control_STATE & 1<<6), Executive_Actions_Emu[1], Executive_Actions_Bool[1]);
  }
  EA_Control_LAST = EA_Control_STATE;
}
