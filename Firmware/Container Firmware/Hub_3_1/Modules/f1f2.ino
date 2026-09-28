// Transmissions
if (Analog_Con) {module_transmission(Analog_, Analog, 8, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}
if (Analog_Throttle_Con) {module_transmission(Analog_Throttle_, Analog, 9, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Analog_Con or Analog_Throttle_Con){Analog_Action();}

// Action
void Analog_Action() {
  if (Analog[0] != Analog_STATE) {
    Analog_STATE = Analog[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (Analog[0] & 2) {
        trimy = 0;
        trimp = 0;
        trimr = 0;
        cruise_control = 0;
        myWheel.throttle = 0;
      }
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
      if (Analog[0] & 8) {
        vehicleType = rover;
      } else if (Analog[0] & 16) {
        vehicleType = plane;
      } else {
        vehicleType = rocket;
      }
      if(Analog[0] & 32){
        analog_mode = 1;
      } else {
        analog_mode = 0;
      }
      if (Analog_Con) {
        if((Analog[0] & 64) && !(currentActionStatus & GEAR_ACTION)){
          mySimpit.activateAction(GEAR_ACTION);
        }
        if(!(Analog[0] & 64) && (currentActionStatus & GEAR_ACTION)){
          mySimpit.deactivateAction(GEAR_ACTION);
        }
      }

    } else {
      // Controller is in Keyboard Emulation mode
      setKey(Analog[0] & 1, Analog_Trim, Analog_flag[0]);
      setKey(Analog[0] & 2, Analog_Reset_Trim, Analog_flag[1]);
      setKey(Analog[0] & 4, Analog_Brakes, Analog_flag[2]);
      setKey_Switch(Analog[0] & 8, Analog_RVR, Analog_flag[3]);
      setKey_Switch(Analog[0] & 16, Analog_PLN, Analog_flag[4]);
      setKey_Switch(Analog[0] & 32, Analog_TRN, Analog_flag[5]);
      setKey_Switch(Analog[0] & 64, Analog_Gear, Analog_flag[6]);
    }
    Analog_LAST = Analog_STATE;
  }

  // Rotation 
  if (!keyboardEmulation) {
    if (analog_mode == 1) {
      // Plane
      if (vehicleType == 0) {
        updateAnalogValues(ANALOG_ROTATION_MESSAGE, Analog_axis2, Analog_axis1, Analog_axis0);
        updateAnalogValues(ANALOG_WHEEL_MESSAGE, Analog_axis1_wheels, Analog_axis0_wheels, 0);
    
        // Trim
        if (Analog[0] & 1) {
          trimy = Analog_axis2;
          trimp = Analog_axis1;
          trimr = Analog_axis0;
        }
        updateAnalogValues(ANALOG_ROTATION_MESSAGE, checkTrim(trimy, Analog_axis2), checkTrim(trimp, Analog_axis1), checkTrim(trimr, Analog_axis0));
      }
      
      // Rocket
      if (vehicleType == 1) {
        updateAnalogValues(ANALOG_ROTATION_MESSAGE, Analog_axis0, Analog_axis1, Analog_axis2);
        updateAnalogValues(ANALOG_WHEEL_MESSAGE, 0, 0, 0);
      }
      
      // Rover
      if (vehicleType == 2) {
        updateAnalogValues(ANALOG_ROTATION_MESSAGE, Analog_axis2, Analog_axis1, Analog_axis0);
      }
      updateAnalogValues(ANALOG_TRANSLATION_MESSAGE, 0, 0, 0);
    }

    // Translation
    if (analog_mode == 0) {
      
      updateAnalogValues(ANALOG_TRANSLATION_MESSAGE, Analog_axis0, Analog_axis1, Analog_axis2);
      updateAnalogValues(ANALOG_ROTATION_MESSAGE, 0, 0, 0);
      
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
    // Execute (send only when value changed)
    sendRotationIfChanged();
    sendTranslationIfChanged();
    if (Analog_Throttle_Con) {
      sendThrottleIfChanged(Rotation_throttle, Rotation_throttleOld);
    }
    sendWheelIfChanged();
    
  } else {
    // Yaw (axis2), Pitch (axis1), Roll (axis0)
    setAnalogAxisKey(Analog_axis2, deadZone_max, true, Analog_Twist_Right, Analog_flag[7]);
    setAnalogAxisKey(Analog_axis2, deadZone_min, false, Analog_Twist_Left, Analog_flag[8]);
    setAnalogAxisKey(Analog_axis1, deadZone_max, true, Analog_Forward, Analog_flag[9]);
    setAnalogAxisKey(Analog_axis1, deadZone_min, false, Analog_Backward, Analog_flag[10]);
    setAnalogAxisKey(Analog_axis0, deadZone_max, true, Analog_Left, Analog_flag[11]);
    setAnalogAxisKey(Analog_axis0, deadZone_min, false, Analog_Right, Analog_flag[12]);
  }
}

// Keyboard Emulation
  #define Analog_Trim                         ':'
  #define Analog_Reset_Trim                   '?'
  #define Analog_Brakes                       'b'
  #define Analog_Gear                         'g'
  #define Analog_RVR                          '3'
  // RKT mode is not actually an input
  #define Analog_PLN                          '5'
  #define Analog_TRN                          '6'
  // ROT mode is not actually an input
  #define Analog_Twist_Right                  'w'
  #define Analog_Twist_Left                   's'
  #define Analog_Forward                      'a'
  #define Analog_Backward                     'd'
  #define Analog_Left                         'q'
  #define Analog_Right                        'e'