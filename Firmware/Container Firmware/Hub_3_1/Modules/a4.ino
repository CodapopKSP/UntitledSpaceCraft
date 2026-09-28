// Transmissions
if (EA_Groups_Ctrl_Con) {module_transmission(EA_Groups_Ctrl_, EA_Groups_Ctrl, ONE_BYTE, EA_Groups_Dspl_, EA_Groups_Dspl, ONE_BYTE);}

// Enable Action
if (EA_Groups_Ctrl_Con){EA_Groups_Action();}

// Action Results
const int EA_Groups_List[5] = {1, 2, 3, 4, 5};

// Action
void EA_Groups_Action() {
  if (EA_Groups_Ctrl[0] != EA_Groups_STATE) {
    EA_Groups_STATE = EA_Groups_Ctrl[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 5; i++) {
        setSimpitAction(EA_Groups_STATE & 1<<i, EA_Groups_List[i], EA_Groups_flag[i], simpitToggleCAG);
      }
      setSimpitAction(EA_Groups_STATE & 32, STAGE_ACTION, EA_Groups_flag[5], simpitActivateAction);
      setSimpitAction(EA_Groups_STATE & 64, ABORT_ACTION, EA_Groups_flag[6], simpitActivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 7; i++) {
        setKey(EA_Groups_STATE & 1<<i, EA_Groups_Emulation_Keys[i], EA_Groups_flag[i]);
      }
    }
  }
  EA_Groups_LAST = EA_Groups_STATE;
}

// Message Handler
        if (EA_Groups_Ctrl_Con) {
          bool EA_Groups_Dspl_b[8] = {0,0,0,0,0,0,0,0};
          for (int i = 0; i < 8; i++) {
            EA_Groups_Dspl_b[i] = (myAG.is_action_activated(i+1));
          }
          for (int i = 0; i < 8; i++) {
            bitWrite(EA_Groups_Dspl[0], i, EA_Groups_Dspl_b[i]);
          }
        }

// Keyboard Emulation
  #define EA_Groups_Stage                     ' '
  #define EA_Groups_Abort                     KEY_BACKSPACE 
  #define EA_Groups_Action_Group_1            '1'
  #define EA_Groups_Action_Group_2            '2'
  #define EA_Groups_Action_Group_3            '3'
  #define EA_Groups_Action_Group_4            '4'
  #define EA_Groups_Action_Group_5            '5'
  

// definitions
  const uint8_t EA_Groups_Emulation_Keys[7] = {
    EA_Groups_Action_Group_1,
    EA_Groups_Action_Group_2,
    EA_Groups_Action_Group_3,
    EA_Groups_Action_Group_4,
    EA_Groups_Action_Group_5,
    EA_Groups_Stage,
    EA_Groups_Abort
  };