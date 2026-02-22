// Transmissions
if (Action2_Ctrl_Con) {module_transmission(Action2_Ctrl_, Action2_Ctrl, TWO_BYTES, Action2_Dspl_, Action2_Dspl, TWO_BYTES);}

// Enable Action
if (Action2_Ctrl_Con){Action2_Action();}

// Action Results
const int AG2_List[10] = {11,16,12,17,13,18,14,19,15,20};

// Action
void Action2_Action() {
  int Action2_combinedBytes = Action2_Ctrl[0] + (Action2_Ctrl[1]*256);
  if (Action2_combinedBytes != Action2_STATE) {
    Action2_STATE = Action2_combinedBytes;
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 10; i++) {
        setSimpitAction(Action2_STATE & 1<<i, AG2_List[i], Action2_flag[i], simpitToggleCAG);
      }
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 10; i++) {
        setKey(Action2_STATE & 1<<i, Action2_Emulation_Keys[i], Action2_flag[i]);
      }
    }
  }
  Action2_LAST = Action2_STATE;
}

// Message Handler
          if (Action2_Ctrl_Con) {
            bool Action2_Dspl_b[10] = {};
            for (int i = 0; i < 10; i++) {
              Action2_Dspl_b[i] = (myAG.is_action_activated(AG2_List[i]));
            }
            for (int i = 0; i < 8; i++) {
              bitWrite(Action2_Dspl[0], i, Action2_Dspl_b[i]);
            }
            for (int i = 0; i < 2; i++) {
              bitWrite(Action2_Dspl[1], i, Action2_Dspl_b[i+8]);
            }
          }

// Keyboard Emulation
  #define Action_Group_11                     '1'
  #define Action_Group_12                     '2'
  #define Action_Group_13                     '3'
  #define Action_Group_14                     '4'
  #define Action_Group_15                     '5'
  #define Action_Group_16                     '6'
  #define Action_Group_17                     '7'
  #define Action_Group_18                     '8'
  #define Action_Group_19                     '9'
  #define Action_Group_20                     '0'

// definitions
  const uint8_t Action2_Emulation_Keys[10] = {
    Action_Group_11,
    Action_Group_12,
    Action_Group_13,
    Action_Group_14,
    Action_Group_15,
    Action_Group_16,
    Action_Group_17,
    Action_Group_18,
    Action_Group_19,
    Action_Group_20,
  };