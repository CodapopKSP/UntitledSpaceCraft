// Transmissions
if (Executive_Actions_Con) {module_transmission(Executive_Actions_, Executive_Actions, ONE_BYTE, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Executive_Actions_Con){Executive_Actions_Action();}

// Action
void Executive_Actions_Action() {
  if (Executive_Actions[0] != Executive_Actions_STATE) {
    Executive_Actions_STATE = Executive_Actions[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setSimpitAction(Executive_Actions_STATE & 1, STAGE_ACTION, Executive_Actions_flag[0], simpitActivateAction);
      setSimpitAction(Executive_Actions_STATE & 2, ABORT_ACTION, Executive_Actions_flag[1], simpitActivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      setKey(Executive_Actions_STATE & 1, Executive_Actions_Stage, Executive_Actions_flag[0]);
      setKey(Executive_Actions_STATE & 2, Executive_Actions_Abort, Executive_Actions_flag[1]);
    }
  }
  Executive_Actions_LAST = Executive_Actions_STATE;
}

// Keyboard Emulation
  #define Executive_Actions_Stage             ' '
  #define Executive_Actions_Abort             KEY_BACKSPACE