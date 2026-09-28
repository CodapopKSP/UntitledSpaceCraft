// Transmissions
if (Abort_Con) {module_transmission(Abort_, Abort_Button, ONE_BYTE, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Abort_Con){Abort_Action();}

// Action
void Abort_Action() {
  // Abort Button
  if (Abort_Button[0] != Abort_STATE) {
    Abort_STATE = Abort_Button[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setSimpitAction(Abort_STATE & 1, ABORT_ACTION, Abort_flag, simpitActivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      setKey(Abort_Button[0] & 1, Abort_Abort, Abort_flag);
    }
  }
  Abort_LAST = Abort_STATE;
}

// Keyboard Emulation
  #define Abort_Abort                         KEY_BACKSPACE
