// Transmissions
if (EA_Control_Ctrl_Con) {module_transmission(EA_Control_Ctrl_, EA_Control_Ctrl, ONE_BYTE, EA_Control_Dspl_, EA_Control_Dspl, ONE_BYTE);}

// Enable Action
if (EA_Control_Ctrl_Con){EA_Control_Action();}

// Action
void EA_Control_Action() {
  if (EA_Control_Ctrl[0] != EA_Control_STATE) {
    EA_Control_STATE = EA_Control_Ctrl[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setSimpitAction(EA_Control_STATE & 1, LIGHT_ACTION, EA_Control_flag[0], simpitToggleAction);
      setSimpitAction(EA_Control_STATE & 2, GEAR_ACTION, EA_Control_flag[1], simpitToggleAction);
      setSimpitAction(EA_Control_STATE & 4, AP_STABILITYASSIST, EA_Control_flag[2], simpitSetSASMode);
      setSimpitAction_Switch(EA_Control_STATE & 8, SAS_ACTION, EA_Control_flag[3], simpitActivateAction, simpitDeactivateAction);
      setSimpitAction_Switch(EA_Control_STATE & 16, RCS_ACTION, EA_Control_flag[4], simpitActivateAction, simpitDeactivateAction);
      setSimpitAction(EA_Control_STATE & 32, STAGE_ACTION, EA_Control_flag[5], simpitActivateAction);
      setSimpitAction(EA_Control_STATE & 64, ABORT_ACTION, EA_Control_flag[6], simpitActivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      setKey(EA_Control_STATE & 1, EA_Control_Light, EA_Control_flag[0]);
      setKey(EA_Control_STATE & 2, EA_Control_Gear, EA_Control_flag[1]);
      setKey(EA_Control_STATE & 4, EA_Control_Hold, EA_Control_flag[2]);
      setKey_Switch(EA_Control_STATE & 8, EA_Control_SAS, EA_Control_flag[3]);
      setKey_Switch(EA_Control_STATE & 16, EA_Control_RCS, EA_Control_flag[4]);
      setKey(EA_Control_STATE & 32, EA_Control_Stage, EA_Control_flag[5]);
      setKey(EA_Control_STATE & 64, EA_Control_Abort, EA_Control_flag[6]);
    }
  }
  EA_Control_LAST = EA_Control_STATE;
}

// Keyboard Emulation
  #define EA_Control_Stage                    ' '
  #define EA_Control_Abort                    KEY_BACKSPACE
  #define EA_Control_Light                    'u'
  #define EA_Control_Gear                     'g'
  #define EA_Control_Hold                     '1'
  #define EA_Control_SAS                      't'
  #define EA_Control_RCS                      'r'

// definitions
  const uint8_t EA_Control_Emulation_Keys[8] = {
    EA_Control_Light,
    EA_Control_Gear,
    EA_Control_Hold,
    EA_Control_SAS,
    EA_Control_RCS,
    EA_Control_Stage,
    EA_Control_Abort
  };