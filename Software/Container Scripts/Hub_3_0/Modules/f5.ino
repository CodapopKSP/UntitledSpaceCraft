// Transmissions
if (Translation_Con) {module_transmission(Translation_, Translation, 9, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Translation_Con){Translation_Action();}

// Action Results
uint8_t EVA_List_Analog[10] = {
  'b',
  'f',
  ' ',
  'r',
  KEY_LEFT_SHIFT,
  KEY_LEFT_CTRL,
  'w',
  'a',
  's',
  'd',
};

// Action
void Translation_Action() {
  if (Translation[0] != Translation_STATE) {
    Translation_STATE = Translation[0];
  
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (On_EVA and !EVA_Ctrl_Con) {
        setKey(Translation_axis0 < 0, EVA_List_Analog[9], EVA_flag[0]);
        setKey(Translation_axis0 > 0, EVA_List_Analog[7], EVA_flag[1]);
        setKey(Translation_axis2 < 0, EVA_List_Analog[4], EVA_flag[2]);
        setKey(Translation_axis2 > 0, EVA_List_Analog[5], EVA_flag[3]);
        setKey(Translation_axis1 < 0, EVA_List_Analog[6], EVA_flag[4]);
        setKey(Translation_axis1 > 0, EVA_List_Analog[8], EVA_flag[5]);
        setKey(Translation[0] & 8, EVA_List_Analog[2], EVA_flag[6]);
        setKey(Translation[0] & 1, EVA_List_Analog[1], EVA_flag[7]);
        setKey(Translation[0] & 16, EVA_List_Analog[0], EVA_flag[8]);
        setKey_Switch(Translation[0] & 2, EVA_List_Analog[3], EVA_flag[9]);
      } else {
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
      }
    } else {
      // Controller is in Keyboard Emulation mode
      setSimpitAction_Switch(Translation[0] & 2, Translation_Precision_Control, Translation_flag[0], tapKey, tapKey);
      setSimpitAction_Switch(Translation[0] & 4, Translation_Brakes_Lock, Translation_flag[1], tapKey, tapKey);
      setSimpitAction(Translation[0] & 8, Translation_Brakes, Translation_flag[2], tapKey);
      setSimpitAction(Translation[0] & 16, Translation_Reset_Cruise, Translation_flag[3], tapKey);
      setSimpitAction(Translation[0] & 32, Translation_Cruise, Translation_flag[4], tapKey);
    }
    Translation_LAST = Translation_STATE;Translation_LAST = Translation_STATE;
  }
  if (!keyboardEmulation) {
    if (vehicleType != rover) {
      if (precision) {
        updateAnalogValues(ANALOG_TRANSLATION_MESSAGE, Translation_axis0/prec_divide, Translation_axis1/prec_divide, Translation_axis2/prec_divide);
      } else {
        updateAnalogValues(ANALOG_TRANSLATION_MESSAGE, Translation_axis0, Translation_axis1, Translation_axis2);
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
    sendTranslationIfChanged();
    sendWheelIfChanged();
  } else {
  
    setAnalogAxisKey(Translation_axis2, deadZone_max, true,  Translation_Twist_Right,   Translation_flag[6]);
    setAnalogAxisKey(Translation_axis2, deadZone_min, false, Translation_Twist_Left,    Translation_flag[7]);
    setAnalogAxisKey(Translation_axis1, deadZone_max, true,  Translation_Forward,       Translation_flag[8]);
    setAnalogAxisKey(Translation_axis1, deadZone_min, false, Translation_Backward,      Translation_flag[9]);
    setAnalogAxisKey(Translation_axis0, deadZone_max, true,  Translation_Right,         Translation_flag[10]);
    setAnalogAxisKey(Translation_axis0, deadZone_min, false, Translation_Left,          Translation_flag[11]);
  }
}

// Keyboard Emulation
  #define Translation_Brakes                  'b'
  #define Translation_Brakes_Lock             'b'
  #define Translation_Cruise                  '8'
  #define Translation_Reset_Cruise            '9'
  #define Translation_Precision_Control       '0'
  #define Translation_Forward                 'i'
  #define Translation_Backward                'k'
  #define Translation_Left                    'j'
  #define Translation_Right                   'l'
  #define Translation_Twist_Left              'h'
  #define Translation_Twist_Right             'n'