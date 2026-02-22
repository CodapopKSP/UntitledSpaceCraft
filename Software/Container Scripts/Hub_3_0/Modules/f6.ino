// Transmissions
if (Throttle_Con) {module_transmission(Throttle_, Throttle, 3, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Throttle_Con){Throttle_Action();}

// Action
void Throttle_Action() {
  if (Throttle[0] != Throttle_STATE) {
    Throttle_STATE = Throttle[0];
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (Throttle[0] & 1) {
        throttle_pcont = true;
      } else {
        throttle_pcont = false;
      }
      if (Throttle[0] & 2) {
        throttle = 0;
      }
      sendThrottleIfChanged(throttle, throttleOld);
    } else {
      // Controller is in Keyboard Emulation mode
      setSimpitAction_Switch(Throttle[0] & 1, Throttle_Precision, Throttle_flag[0], tapKey, tapKey);
      setSimpitAction(Throttle[0] & 2, Throttle_Min, Throttle_flag[1], tapKey);
      setAnalogAxisKey(throttle, throttle_min+100, true,  Throttle_Forward,   Throttle_flag[2]);
    }
  }
  Throttle_LAST = Throttle_STATE;
}

// Keyboard Emulation
  #define Throttle_Precision                  '1'
  #define Throttle_Min                        '2'
  // Throttle Max is not actually an input
  #define Throttle_Forward                    '0'
