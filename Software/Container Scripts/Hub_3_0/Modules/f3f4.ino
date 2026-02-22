// Transmissions
if (Rotation_Throttle_Con) {module_transmission(Rotation_Throttle_, Rotation, 9, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}
if (Rotation_Con) {module_transmission(Rotation_, Rotation, 7, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Rotation_Throttle_Con or Rotation_Con){Rotation_Action();}

// Action
void Rotation_Action() {
  if (Rotation[0] != Rotation_STATE) {
    Rotation_STATE = Rotation[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (Rotation_Throttle_Con) {
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
      }
      if (Rotation_Con) {
        if ((Rotation[0] & 1) && !(currentActionStatus & LIGHT_ACTION)){
          mySimpit.activateAction(LIGHT_ACTION);
        }
        if ((Rotation[0] & 1) && (currentActionStatus & LIGHT_ACTION)){
          mySimpit.deactivateAction(LIGHT_ACTION);
        }
        if (Rotation[0] & 2) {
          trimy = 0;
          trimp = 0;
          trimr = 0;
        }
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
        if((Rotation[0] & 32) && !(currentActionStatus & GEAR_ACTION)){
          mySimpit.activateAction(GEAR_ACTION);
        }
        if(!(Rotation[0] & 32) && (currentActionStatus & GEAR_ACTION)){
          mySimpit.deactivateAction(GEAR_ACTION);
        }
      }
    } else {
      // Controller is in Keyboard Emulation mode
      setSimpitAction(Rotation[0] & 1, Rotation_Light, Rotation_flag[0], tapKey);
      setSimpitAction(Rotation[0] & 2, Rotation_Reset_Trim, Rotation_flag[1], tapKey);
      setSimpitAction(Rotation[0] & 4, Rotation_Trim, Rotation_flag[2], tapKey);
      setSimpitAction_Switch(Rotation[0] & 8, Rotation_RVR, Rotation_flag[3], tapKey, tapKey);
      setSimpitAction_Switch(Rotation[0] & 16, Rotation_PLN, Rotation_flag[4], tapKey, tapKey);
      setSimpitAction_Switch(Rotation[0] & 32, Rotation_Gear, Rotation_flag[5], tapKey, tapKey);
    }
    Rotation_LAST = Rotation_STATE;
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
    setAnalogAxisKey(Rotation_axis2, deadZone_max, true,  Rotation_Twist_Right,   Rotation_flag[6]);
    setAnalogAxisKey(Rotation_axis2, deadZone_min, false, Rotation_Twist_Left,    Rotation_flag[7]);
    setAnalogAxisKey(Rotation_axis1, deadZone_max, true,  Rotation_Forward,       Rotation_flag[8]);
    setAnalogAxisKey(Rotation_axis1, deadZone_min, false, Rotation_Backward,      Rotation_flag[9]);
    setAnalogAxisKey(Rotation_axis0, deadZone_max, true,  Rotation_Right,         Rotation_flag[10]);
    setAnalogAxisKey(Rotation_axis0, deadZone_min, false, Rotation_Left,          Rotation_flag[11]);
  }
}

// Keyboard Emulation
  #define Rotation_Gear                       'g'
  #define Rotation_Light                      'u'
  #define Rotation_Reset_Trim                 '?'
  #define Rotation_Trim                       ':'
  #define Rotation_PLN                        '3'
  // RKT mode is not actually an input
  #define Rotation_RVR                        '5'
  #define Rotation_Forward                    'w'
  #define Rotation_Backward                   's'
  #define Rotation_Left                       'a'
  #define Rotation_Right                      'd'
  #define Rotation_Twist_Left                 'q'
  #define Rotation_Twist_Right                'e'