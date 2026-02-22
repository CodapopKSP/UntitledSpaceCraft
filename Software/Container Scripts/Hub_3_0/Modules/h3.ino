// Transmissions
if (Action3_Ctrl_Con) {module_transmission(Action3_Ctrl_, Action3_Ctrl, TWO_BYTES, Action3_Dspl_, Action3_Dspl, TWO_BYTES);}

// Enable Action
if (Action3_Ctrl_Con){Action3_Action();}

// Action Results
const int AG3_List[10] = {21,26,22,27,23,28,24,29,25,30};

// Action
void Action3_Action() {
  int Action3_combinedBytes = Action3_Ctrl[0] + (Action3_Ctrl[1]*256);
  if (Action3_combinedBytes != Action3_STATE) {
    Action3_STATE = Action3_combinedBytes;
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 10; i++) {
        setSimpitAction(Action3_STATE & 1<<i, AG3_List[i], Action3_flag[i], simpitToggleCAG);
      }
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 10; i++) {
        setKey(Action3_STATE & 1<<i, Action3_Emulation_Keys[i], Action3_flag[i]);
      }
    }
  }
  Action2_LAST = Action2_STATE;
}

// Message Handler
          if (Action3_Ctrl_Con) {
            bool Action3_Dspl_b[10] = {};
            for (int i = 0; i < 10; i++) {
              Action3_Dspl_b[i] = (myAG.is_action_activated(AG3_List[i]));
            }
            for (int i = 0; i < 8; i++) {
              bitWrite(Action3_Dspl[0], i, Action3_Dspl_b[i]);
            }
            for (int i = 0; i < 2; i++) {
              bitWrite(Action3_Dspl[1], i, Action3_Dspl_b[i+8]);
            }
          }

// Keyboard Emulation
  #define Action_Group_21                     '1'
  #define Action_Group_22                     '2'
  #define Action_Group_23                     '3'
  #define Action_Group_24                     '4'
  #define Action_Group_25                     '5'
  #define Action_Group_26                     '6'
  #define Action_Group_27                     '7'
  #define Action_Group_28                     '8'
  #define Action_Group_29                     '9'
  #define Action_Group_30                     '0'

// definitions
  const uint8_t Action3_Emulation_Keys[10] = {
    Action_Group_21,
    Action_Group_22,
    Action_Group_23,
    Action_Group_24,
    Action_Group_25,
    Action_Group_26,
    Action_Group_27,
    Action_Group_28,
    Action_Group_29,
    Action_Group_30,
  };