// Transmissions
if (Stage_Con) {module_transmission(Stage_, Stage_Button, ONE_BYTE, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Stage_Con){Stage_Action();}

// Action
void Stage_Action() {
  // Stage Button
  if (Stage_Button[0] != Stage_STATE) {
    Stage_STATE = Stage_Button[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setSimpitAction(Stage_STATE & 1, STAGE_ACTION, Stage_flag, simpitActivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      setKey(Stage_Button[0] & 1, Stage_Stage, Stage_flag);
    }
  }
  Stage_LAST = Stage_STATE;
}

// Keyboard Emulation
  #define Stage_Stage                         ' '
