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
      if (Action_STATE & 1<<i) {
        mySimpit.toggleCAG(AG_List[i]);
      }
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
      if (Action2_STATE & 1<<i) {
        mySimpit.toggleCAG(AG2_List[i]);
      }
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
      if (Action3_STATE & 1<<i) {
        mySimpit.toggleCAG(AG3_List[i]);
      }
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
      if ((Ctrl_Sys_STATE & 1<<i) and (currentActionStatus & SAS_ACTION)) {
        mySimpit.setSASMode(SASMode[i]);
      }
    }
  }
  Ctrl_Sys_LAST = Ctrl_Sys_STATE;

  // SAS/RCS
  if((ControlSys_combinedBytes & 1024) && (!SAS_pushed)){
    mySimpit.activateAction(SAS_ACTION);
    SAS_pushed = true;
  }
  if(!(ControlSys_combinedBytes & 1024) && (SAS_pushed)){
    mySimpit.deactivateAction(SAS_ACTION);
    SAS_pushed = false;
  }
  if((ControlSys_combinedBytes & 2048) && (!RCS_pushed)){
    mySimpit.activateAction(RCS_ACTION);
    RCS_pushed = true;
  }
  if(!(ControlSys_combinedBytes & 2048) && (RCS_pushed)){
    mySimpit.deactivateAction(RCS_ACTION);
    RCS_pushed = false;
  }
}

void Navigation_Action() {
  if (Navigation[0] != Navigation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation[0] != Navigation_STATE) {
    Navigation_STATE = Navigation[0];

    if (Navigation_STATE & 1) {
      KEY.keyCode = Nav_List[0];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 2) {
      KEY.keyCode = Nav_List[1];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 4) {
      KEY.keyCode = 0xA0;
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      delay(50);

      KEY.keyCode = 0x09;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      delay(50);

      KEY.keyCode = 0xA0;
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
    }
    if (Navigation_STATE & 8) {
      KEY.keyCode = Nav_List[3];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 16) {
      KEY.keyCode = Nav_List[4];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 32) {
      mySimpit.cycleNavBallMode();
    }
    
    if((Navigation_STATE & 64) && !MAP_on){
      KEY.keyCode = Nav_List[6];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
      if (!NAV_on) {
        KEY.keyCode = Nav_List[7];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
    if(!(Navigation_STATE & 64) && MAP_on){
      KEY.keyCode = Nav_List[6];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
      if (!NAV_on) {
        KEY.keyCode = Nav_List[7];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
    if((Navigation_STATE & 128) && !NAV_on){
      KEY.keyCode = Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      NAV_on = true;
    }
    if(!(Navigation_STATE & 128) && NAV_on){
      KEY.keyCode = Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      NAV_on = false;
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

    for (int i = 1; i < 7; i++) {
      if (Time_STATE & 1<<i) {
        if (i > 1) {
          KEY.keyCode = Time_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        } else {
          timewarpToMessage TIMEW(TW_type, TW_delay);
          mySimpit.send(TIMEWARP_TO_MESSAGE, TIMEW);
        }
      }
    }

    // Phys Warp
    if (Time_STATE & 1) {
      KEY.keyCode = Time_List[0];
    mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if ((Time_STATE & 128) and !F9_press) {
      KEY.keyCode = Time_List[7];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = true;
    }
    if (!(Time_STATE & 128) and F9_press) {
      KEY.keyCode = Time_List[7];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = false;
      KEY.modifier = 0;
    }
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
    if (Stage_Abort_STATE & 1) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (Stage_Abort_STATE & 2) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  Stage_Abort_LAST = Stage_Abort_STATE;
}

void Translation_Action() {
  
  if (On_EVA and !EVA_Ctrl_Con) {

    // Walking/Flying Controls
    if ((Translation_axis0 < 0)and (!a_is_down)) {
      KEY.keyCode = EVA_List_Analog[9];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      a_is_down = true;
    }
    if ((Translation_axis0 >= 0)and (a_is_down)) {
      KEY.keyCode = EVA_List_Analog[9];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      a_is_down = false;
    }
    if ((Translation_axis0 > 0)and (!d_is_down)) {
      KEY.keyCode = EVA_List_Analog[7];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      d_is_down = true;
    }
    if ((Translation_axis0 <= 0)and (d_is_down)) {
      KEY.keyCode = EVA_List_Analog[7];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      d_is_down = false;
    }
    if ((Translation_axis2 < 0)and (!shift_is_down)) {
      KEY.keyCode = EVA_List_Analog[4];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      shift_is_down = true;
    }
    if ((Translation_axis2 >= 0)and (shift_is_down)) {
      KEY.keyCode = EVA_List_Analog[4];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      shift_is_down = false;
    }
    if ((Translation_axis2 > 0)and (!ctrl_is_down)) {
      KEY.keyCode = EVA_List_Analog[5];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      ctrl_is_down = true;
    }
    if ((Translation_axis2 <= 0)and (ctrl_is_down)) {
      KEY.keyCode = EVA_List_Analog[5];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      ctrl_is_down = false;
    }
    if ((Translation_axis1 < 0)and (!w_is_down)) {
      KEY.keyCode = EVA_List_Analog[6];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      w_is_down = true;
    }
    if ((Translation_axis1 >= 0)and (w_is_down)) {
      KEY.keyCode = EVA_List_Analog[6];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      w_is_down = false;
    }
    if ((Translation_axis1 > 0)and (!s_is_down)) {
      KEY.keyCode = EVA_List_Analog[8];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      s_is_down = true;
    }
    if ((Translation_axis1 <= 0)and (s_is_down)) {
      KEY.keyCode = EVA_List_Analog[8];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      s_is_down = false;
    }

    // Jump
    if ((Translation[0] & 8) and (!space_is_down)) {
      KEY.keyCode = EVA_List_Analog[2];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      space_is_down = true;
    }
    if (!(Translation[0] & 8) and (space_is_down)) {
      KEY.keyCode = EVA_List_Analog[2];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      space_is_down = false;
    }
    // Grab
    if ((Translation[0] & 1) and (!f_is_down)) {
      KEY.keyCode = EVA_List_Analog[1];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      f_is_down = true;
    }
    if (!(Translation[0] & 1) and (f_is_down)) {
      KEY.keyCode = EVA_List_Analog[1];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      f_is_down = false;
    }
    // Board
    if ((Translation[0] & 16) and (!b_is_down)) {
      KEY.keyCode = EVA_List_Analog[0];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      b_is_down = true;
    }
    if (!(Translation[0] & 16) and (b_is_down)) {
      KEY.keyCode = EVA_List_Analog[0];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      b_is_down = false;
    }
    // Jet
    if ((Translation[0] & 2) and (!r_is_down)) {
      KEY.keyCode = EVA_List_Analog[3];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      r_is_down = true;
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
    }
    if (!(Translation[0] & 2) and (r_is_down)) {
      KEY.keyCode = EVA_List_Analog[3];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      r_is_down = false;
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
    }
  }

  if (!On_EVA) {
    // Precision Control
    if (Translation[0] & 2) {
      precision = true;
    } else {
      precision = false;
    }
  
    // Parking Break On
    if ((Translation[0] & 4) and !parking_break){
      mySimpit.activateAction(BRAKES_ACTION);
      parking_break = true;
      cruise_control = 0;
    }
  
    // Parking Break Off
    if(!(Translation[0] & 4) && !brakes_pushed && parking_break){
      mySimpit.deactivateAction(BRAKES_ACTION);
      parking_break = false;
    }
  
    // Brakes
    if((Translation[0] & 8) && !brakes_pushed && !parking_break){
      mySimpit.activateAction(BRAKES_ACTION);
      cruise_control = 0;
      brakes_pushed = true;
    }
    if(!(Translation[0] & 8) && brakes_pushed){
      brakes_pushed = false;
      if (!parking_break) {
        mySimpit.deactivateAction(BRAKES_ACTION);
      }
    }
  
    // Reset Cruise
    if (Translation[0] & 16) {
      cruise_control = 0;
    }

    if (vehicleType != rover) {
      if (precision) {
        myTranslation.X = Translation_axis0/prec_divide;
        myTranslation.Y = Translation_axis1/prec_divide; // Maybe flip this axis
        myTranslation.Z = Translation_axis2/prec_divide;
      } else {
        myTranslation.X = Translation_axis0;
        myTranslation.Y = Translation_axis1; // Maybe flip this axis
        myTranslation.Z = Translation_axis2;
      }
    } else {
      // Set Cruise Control and Wheel Throttle/Steering
      if (Translation[0] & 1) {
        cruise_control = Translation_axis1_wheels;
      }
      if ((cruise_control != 0) and (Translation_axis1_wheels <= cruise_control)) {
        myWheel.throttle = cruise_control;
      } else {
        myWheel.throttle = Translation_axis1_wheels;
      }
      myWheel.steer = Translation_axis0_wheels;
    }

    // Execute
    if(memcmp(&myTranslation, &myTranslationOld, sizeof(translationMessage)) != 0)
    {
      mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
      myTranslationOld = myTranslation;
    }
  
    if(memcmp(&myWheel, &myWheelOld, sizeof(wheelMessage)) != 0)
    {
      mySimpit.send(WHEEL_MESSAGE, myWheel);
      myWheelOld = myWheel;
    }
  }
}

void Rotation_Action() {
  if (Rotation_Throttle_Con) {
    if (Rotation[0] & 2) {
      vehicleType = rover;
    } else if (Rotation[0] & 4) {
      vehicleType = plane;
    } else {
      vehicleType = rocket;
    }

    // Trim
    if (Rotation[0] & 1) {
      Trim_On = true;
    } else {
      Trim_On = false;
    }
    // Reset Trim
    if (Rotation[0] & 8) {
      trimy = 0;
      trimp = 0;
      trimr = 0;
    }
  }

  if (Rotation_Con) {
    if (Rotation[0] != Rotation_LAST) {
      lastDebounceTime_b = millis();
    }
    if (Rotation[0] != Rotation_STATE) {
      Rotation_STATE = Rotation[0];
      if ((Rotation[0] & 1) && !(currentActionStatus & LIGHT_ACTION)){
        mySimpit.activateAction(LIGHT_ACTION);
      }
      if ((Rotation[0] & 1) && (currentActionStatus & LIGHT_ACTION)){
        mySimpit.deactivateAction(LIGHT_ACTION);
      }
    }
    Rotation_LAST = Rotation_STATE;
  
    if((Rotation[0] & 32) && !(currentActionStatus & GEAR_ACTION)){
      mySimpit.activateAction(GEAR_ACTION);
    }
    if(!(Rotation[0] & 32) && (currentActionStatus & GEAR_ACTION)){
      mySimpit.deactivateAction(GEAR_ACTION);
    }

    // Trim
    if (Rotation[0] & 4) {
      Trim_On = true;
    } else {
      Trim_On = false;
    }
  
    if (Rotation[0] & 8) {
      vehicleType = rover;
    } else if (Rotation[0] & 16) {
      vehicleType = plane;
    } else {
      vehicleType = rocket;
    }
  
    // Reset Trim
    if (Rotation[0] & 2) {
      trimy = 0;
      trimp = 0;
      trimr = 0;
    }
  }

  // Plane
  if (vehicleType == 0) {
    myRotation.yaw = Rotation_axis2;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis0;
    myWheel.throttle = Rotation_axis1_wheels;
    myWheel.steer = Rotation_axis0_wheels;

    // Trim
    if (Trim_On) {
      trimy = Rotation_axis2;
      trimp = Rotation_axis1;
      trimr = Rotation_axis0;
    }

    myRotation.yaw = checkTrim(trimy, Rotation_axis2);
    myRotation.pitch = checkTrim(trimp, Rotation_axis1);
    myRotation.roll = checkTrim(trimr, Rotation_axis0);
  }
  
  // Rocket
  if (vehicleType == 1) {
    myRotation.yaw = Rotation_axis0;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis2;
    myWheel.throttle = 0;
    myWheel.steer = 0;
  }
  
  // Rover
  if (vehicleType == 2) {
    myRotation.yaw = Rotation_axis2;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis0;
  }

  if (precision) {
    myRotation.yaw = myRotation.yaw/prec_divide;
    myRotation.pitch = myRotation.pitch/prec_divide;
    myRotation.roll = myRotation.roll/prec_divide;
  }

  // Execute
  if(memcmp(&myRotation, &myRotationOld, sizeof(rotationMessage)) != 0)
  {
    mySimpit.send(ROTATION_MESSAGE, myRotation);
    myRotationOld = myRotation;
  }

  if (Rotation_Throttle_Con) {
    if(memcmp(&Rotation_throttle, &Rotation_throttleOld, sizeof(int)) != 0)
    {
      mySimpit.send(THROTTLE_MESSAGE, Rotation_throttle);
      Rotation_throttleOld = Rotation_throttle;
    }
  }

  if(memcmp(&myWheel, &myWheelOld, sizeof(wheelMessage)) != 0)
  {
    mySimpit.send(WHEEL_MESSAGE, myWheel);
    myWheelOld = myWheel;
  }
}

void Camera_Action() {
  Camera_combinedBytes = Camera[0] + (Camera[1]*256);
  if (Camera_combinedBytes != Camera_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Camera_combinedBytes != Camera_STATE) {
    Camera_STATE = Camera_combinedBytes;

    for (int i = 0; i < 2; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }

    for (int i = 2; i < 8; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        KEY.modifier = KEY_DOWN_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      } else {
        KEY.keyCode = Camera_List[i];
        KEY.modifier = KEY_UP_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      }
    }

    for (int i = 8; i < 10; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
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

    for (int i = 0; i < 4; i++) {
      if ((EVA_STATE & 1<<i) and On_EVA) {
        KEY.keyCode = EVA_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }

    for (int i = 4; i < 11; i++) {
      if ((EVA_combinedBytes & 1<<i) and On_EVA) {
        KEY.keyCode = EVA_List[i];
        KEY.modifier = KEY_DOWN_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      } else {
        KEY.keyCode = EVA_List[i];
        KEY.modifier = KEY_UP_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      }
    }

    if ((EVA_combinedBytes & 1<<2) and (EVA_combinedBytes & 1<<10)and On_EVA) {
      KEY.keyCode = EVA_List[11];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
  }
  EVA_LAST = EVA_STATE;
}

void Throttle_Action() {
  if (Throttle[0] & 1) {
    throttle_pcont = true;
  } else {
    throttle_pcont = false;
  }
  if (Throttle[0] & 2) {
    throttle = 0;
  }
  if(memcmp(&throttle, &throttleOld, sizeof(int)) != 0)
  {
    mySimpit.send(THROTTLE_MESSAGE, throttle);
    throttleOld = throttle;
  }
}

void Navigation_Time_Action() {
  if (Navigation_Time_Ctrl[0] != Navigation_Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation_Time_Ctrl[0] != Navigation_Time_STATE) {
    Navigation_Time_STATE = Navigation_Time_Ctrl[0];

    for (int i = 2; i < 7; i++) {
      if (Navigation_Time_STATE & 1<<i) {
        KEY.keyCode = Navigation_Time_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
    if (Navigation_Time_STATE & 1<<1) {
      timewarpToMessage TIMEW(TW_type, TW_delay);
      mySimpit.send(TIMEWARP_TO_MESSAGE, TIMEW);
    }

    // Phys Warp
    if (Navigation_Time_STATE & 1) {
      KEY.keyCode = Navigation_Time_List[0];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if((Navigation_Time_STATE & 128) && !MAP_on){
      KEY.keyCode = Navigation_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
    }
    if(!(Navigation_Time_STATE & 128) && MAP_on){
      KEY.keyCode = Navigation_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
    }
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
      if (EA_Groups_STATE & 1<<i) {
        mySimpit.toggleCAG(i+1);
      }
    }
    if (EA_Groups_STATE & 32) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (EA_Groups_STATE & 64) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  EA_Groups_LAST = EA_Groups_STATE;
}

void Analog_Action() {
  if (Analog[0] != Analog_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Analog[0] != Analog_STATE) {
    Analog_STATE = Analog[0];
    if (Analog[0] & 4){
      if (Analog[0] & 1) {
        brakes_lock = true;
      } else {
        brakes_lock = false;
      }
      if (!(currentActionStatus & BRAKES_ACTION)) {
        mySimpit.activateAction(BRAKES_ACTION);
      }
    }
    if (!(Analog[0] & 4) && (currentActionStatus & BRAKES_ACTION) && !(brakes_lock)){
      mySimpit.deactivateAction(BRAKES_ACTION);
    }
  }
  Analog_LAST = Analog_STATE;
  if (Analog_Con) {
    if((Analog[0] & 64) && !(currentActionStatus & GEAR_ACTION)){
      mySimpit.activateAction(GEAR_ACTION);
    }
    if(!(Analog[0] & 64) && (currentActionStatus & GEAR_ACTION)){
      mySimpit.deactivateAction(GEAR_ACTION);
    }
  }

  if(Analog[0] & 32){
    analog_mode = 1;
  } else {
    analog_mode = 0;
  }

  if (Analog[0] & 8) {
    vehicleType = rover;
  } else if (Analog[0] & 16) {
    vehicleType = plane;
  } else {
    vehicleType = rocket;
  }

  // Reset Trim
  if (Analog[0] & 2) {
    trimy = 0;
    trimp = 0;
    trimr = 0;
    cruise_control = 0;
    myWheel.throttle = 0;
  }

  // Rotation 
  if (analog_mode == 1) {
    // Plane
    if (vehicleType == 0) {
      myRotation.yaw = Analog_axis2;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis0;
      myWheel.throttle = Analog_axis1_wheels;
      myWheel.steer = Analog_axis0_wheels;
  
      // Trim
      if (Analog[0] & 1) {
        trimy = Analog_axis2;
        trimp = Analog_axis1;
        trimr = Analog_axis0;
      }
  
      myRotation.yaw = checkTrim(trimy, Analog_axis2);
      myRotation.pitch = checkTrim(trimp, Analog_axis1);
      myRotation.roll = checkTrim(trimr, Analog_axis0);
    }
    
    // Rocket
    if (vehicleType == 1) {
      myRotation.yaw = Analog_axis0;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis2;
      myWheel.throttle = 0;
      myWheel.steer = 0;
    }
    
    // Rover
    if (vehicleType == 2) {
      myRotation.yaw = Analog_axis2;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis0;
    }
    myTranslation.X = 0;
    myTranslation.Y = 0;
    myTranslation.Z = 0;
    
  // Translation
  }
  if (analog_mode == 0) {
    
    myTranslation.X = Analog_axis0;
    myTranslation.Y = Analog_axis1;
    myTranslation.Z = Analog_axis2;
    myRotation.yaw = 0;
    myRotation.pitch = 0;
    myRotation.roll = 0;
    
    // Rover
    if (vehicleType == 2) {
      // Cruise
      if (Analog[0] & 1) {
        cruise_control = Analog_axis1_wheels;
      }
      if ((cruise_control != 0) and (Analog_axis1_wheels <= cruise_control)) {
        myWheel.throttle = cruise_control;
      } else {
        myWheel.throttle = Analog_axis1_wheels;
      }
      myWheel.steer = Analog_axis0_wheels;
    }
  }
  // Execute
  if(memcmp(&myRotation, &myRotationOld, sizeof(rotationMessage)) != 0)
  {
    mySimpit.send(ROTATION_MESSAGE, myRotation);
    myRotationOld = myRotation;
  }

  if(memcmp(&myTranslation, &myTranslationOld, sizeof(translationMessage)) != 0)
  {
    mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
    myTranslationOld = myTranslation;
  }

  if (Analog_Throttle_Con) {
    if(memcmp(&Rotation_throttle, &Rotation_throttleOld, sizeof(int)) != 0)
    {
      mySimpit.send(THROTTLE_MESSAGE, Rotation_throttle);
      Rotation_throttleOld = Rotation_throttle;
    }
  }

  if(memcmp(&myWheel, &myWheelOld, sizeof(wheelMessage)) != 0)
  {
    mySimpit.send(WHEEL_MESSAGE, myWheel);
    myWheelOld = myWheel;
  }
}

void EA_Control_Action() {
  int EA_Control_combinedBytes = EA_Control_Ctrl[0];
  if (EA_Control_combinedBytes != EA_Control_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EA_Control_combinedBytes != EA_Control_STATE) {
    EA_Control_STATE = EA_Control_combinedBytes;

    if ((EA_Control_combinedBytes & 1) && !(currentActionStatus & LIGHT_ACTION)){
      mySimpit.activateAction(LIGHT_ACTION);
    }
    if ((EA_Control_combinedBytes & 1) && (currentActionStatus & LIGHT_ACTION)){
      mySimpit.deactivateAction(LIGHT_ACTION);
    }
    if ((EA_Control_combinedBytes & 2) && !(currentActionStatus & GEAR_ACTION)){
    mySimpit.activateAction(GEAR_ACTION);
    }
    if ((EA_Control_combinedBytes & 2) && (currentActionStatus & GEAR_ACTION)){
      mySimpit.deactivateAction(GEAR_ACTION);
    }
    
    // SAS/RCS
    if (EA_Control_combinedBytes & 4) {
      mySimpit.setSASMode(AP_STABILITYASSIST);
    }
    if((EA_Control_combinedBytes & 8) && !(currentActionStatus & SAS_ACTION)){
      mySimpit.activateAction(SAS_ACTION);
    }
    if(!(EA_Control_combinedBytes & 8) && (currentActionStatus & SAS_ACTION)){
      mySimpit.deactivateAction(SAS_ACTION);
    }
    if((EA_Control_combinedBytes & 16) && !(currentActionStatus & RCS_ACTION)){
      mySimpit.activateAction(RCS_ACTION);
    }
    if(!(EA_Control_combinedBytes & 16) && (currentActionStatus & RCS_ACTION)){
      mySimpit.deactivateAction(RCS_ACTION);
    }

    if (EA_Control_STATE & 32) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (EA_Control_STATE & 64) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  EA_Control_LAST = EA_Control_STATE;
}

void Util_Nav_Action() {
  if (Util_Nav_Ctrl[0] != Util_Nav_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Util_Nav_Ctrl[0] != Util_Nav_STATE) {
    Util_Nav_STATE = Util_Nav_Ctrl[0];

    if (On_EVA) {
      for (int i = 0; i < 5; i++) {
        if (Util_Nav_STATE & 1<<i) {
          KEY.keyCode = Util_Nav_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        }
      }
    }
    if (Util_Nav_STATE & 1<<5) {
        KEY.keyCode = Util_Nav_List[5];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    if (Util_Nav_STATE & 1<<6) {
      mySimpit.cycleNavBallMode();
    }
    if((Util_Nav_STATE & 1<<7) && !MAP_on){
      KEY.keyCode = Util_Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
    }
    if(!(Util_Nav_STATE & 1<<7) && MAP_on){
      KEY.keyCode = Util_Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
    }
  }
  Util_Nav_LAST = Util_Nav_STATE;
}

void Util_Time_Action() {
  if (Util_Time_Ctrl[0] != Util_Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Util_Time_Ctrl[0] != Util_Time_STATE) {
    Util_Time_STATE = Util_Time_Ctrl[0];

    if (On_EVA) {
      for (int i = 0; i < 5; i++) {
        if (Util_Time_STATE & 1<<i) {
          KEY.keyCode = Util_Time_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        }
      }
    }
    if((Util_Time_STATE & 1<<5) and !F9_press){
      KEY.keyCode = Util_Time_List[5];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = true;
    }
    if(!(Util_Time_STATE & 1<<5) and F9_press){
      KEY.keyCode = Util_Time_List[5];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      F9_press = false;
    }
    if (Util_Time_STATE & 1<<6) {
      KEY.keyCode = Util_Time_List[6];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Util_Time_STATE & 1<<7) {
      KEY.keyCode = Util_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    
  }
  Util_Time_LAST = Util_Time_STATE;
}
