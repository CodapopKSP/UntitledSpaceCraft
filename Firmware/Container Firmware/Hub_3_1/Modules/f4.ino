// Transmissions
if (Rotation_Throttle_Con) {module_transmission(Rotation_Throttle_, Rotation, 9, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Rotation_Throttle_Con){Rotation_Throttle_Action();}

// Action
void Rotation_Throttle_Action() {
  if (Rotation[0] != Rotation_Throttle_STATE) {
    Rotation_Throttle_STATE = Rotation[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (Rotation[0] & 1) {
        Trim_On = true;
      } else {
        Trim_On = false;
      }
      if (Rotation[0] & 2) {
        vehicleType = rover;
      } else if (Rotation[0] & 4) {
        vehicleType = plane;
      } else {
        vehicleType = rocket;
      }
      if (Rotation[0] & 8) {
        trimy = 0;
        trimp = 0;
        trimr = 0;
      }
    } else {
      // Controller is in Keyboard Emulation mode
      setSimpitAction(Rotation[0] & 1, Rotation_Throttle_Trim, Rotation_Throttle_flag[0], tapKey);
      setSimpitAction_Switch(Rotation[0] & 2, Rotation_Throttle_RVR, Rotation_Throttle_flag[1], tapKey, tapKey);
      setSimpitAction_Switch(Rotation[0] & 4, Rotation_Throttle_PLN, Rotation_Throttle_flag[2], tapKey, tapKey);
      setSimpitAction(Rotation[0] & 8, Rotation_Throttle_Reset_Trim, Rotation_Throttle_flag[3], tapKey);
    }
    Rotation_Throttle_LAST = Rotation_Throttle_STATE;
  }

  if (!keyboardEmulation) {
    // Plane
    if (vehicleType == 0) {
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, Rotation_axis2, Rotation_axis1, Rotation_axis0);
      updateAnalogValues(ANALOG_WHEEL_MESSAGE, Rotation_axis1_wheels, Rotation_axis0_wheels, 0);

      // Trim
      if (Trim_On) {
        trimy = Rotation_axis2;
        trimp = Rotation_axis1;
        trimr = Rotation_axis0;
      }
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, checkTrim(trimy, Rotation_axis2), checkTrim(trimp, Rotation_axis1), checkTrim(trimr, Rotation_axis0));
    }
    
    // Rocket
    if (vehicleType == 1) {
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, Rotation_axis0, Rotation_axis1, Rotation_axis2);
      updateAnalogValues(ANALOG_WHEEL_MESSAGE, 0, 0, 0);
    }
    
    // Rover
    if (vehicleType == 2) {
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, Rotation_axis2, Rotation_axis1, Rotation_axis0);
    }

    if (precision) {
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, myRotation.yaw/prec_divide, myRotation.pitch/prec_divide, myRotation.roll/prec_divide);
    }

    // Execute
    //sendRotationIfChanged();
    if (memcmp(&myRotation, &myRotationOld, sizeof(rotationMessage)) != 0) {
      mySimpit.send(ROTATION_MESSAGE, myRotation);
      myRotationOld = myRotation;
    }
    if (Rotation_Throttle_Con) {
      sendThrottleIfChanged(Rotation_throttle, Rotation_throttleOld);
    }

    sendWheelIfChanged();
  } else {
    setKey(Rotation_axis2 > keyboardEmulation_threshold, Rotation_Throttle_Twist_Right, Rotation_Throttle_flag[6]);
    setKey(Rotation_axis2 < -keyboardEmulation_threshold, Rotation_Throttle_Twist_Left, Rotation_Throttle_flag[7]);
    setKey(Rotation_axis1 > keyboardEmulation_threshold, Rotation_Throttle_Backward, Rotation_Throttle_flag[8]);
    setKey(Rotation_axis1 < -keyboardEmulation_threshold, Rotation_Throttle_Forward, Rotation_Throttle_flag[9]);
    setKey(Rotation_axis0 > keyboardEmulation_threshold, Rotation_Throttle_Right, Rotation_Throttle_flag[10]);
    setKey(Rotation_axis0 < -keyboardEmulation_threshold, Rotation_Throttle_Left, Rotation_Throttle_flag[11]);
    setKey(Rotation_throttle > keyboardEmulation_threshold, Rotation_Throttle_Throttle, Rotation_Throttle_flag[12]);
  }
}

// Keyboard Emulation
  #define Rotation_Throttle_Throttle          '1'
  #define Rotation_Throttle_Reset_Trim        '?'
  #define Rotation_Throttle_Trim              ':'
  #define Rotation_Throttle_PLN               '3'
  // RKT mode is not actually an input
  #define Rotation_Throttle_RVR               '5'
  #define Rotation_Throttle_Forward           'w'
  #define Rotation_Throttle_Backward          's'
  #define Rotation_Throttle_Left              'a'
  #define Rotation_Throttle_Right             'd'
  #define Rotation_Throttle_Twist_Left        'q'
  #define Rotation_Throttle_Twist_Right       'e'