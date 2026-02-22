// Transmissions
if (Action_Ctrl_Con) {module_transmission(Action_Ctrl_, Action_Ctrl, TWO_BYTES, Action_Dspl_, Action_Dspl, TWO_BYTES);}

// Enable Action
if (Action_Ctrl_Con){Action_Action();}

// Action Results
const int AG_List[10] = {1,6,2,7,3,8,4,9,5,10};

// Action
void Action_Action() {
  int Action_combinedBytes = Action_Ctrl[0] + (Action_Ctrl[1]*256);
  if (Action_combinedBytes != Action_STATE) {
    Action_STATE = Action_combinedBytes;
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 10; i++) {
        setSimpitAction(Action_STATE & 1<<i, AG_List[i], Action_flag[i], simpitToggleCAG);
      }
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 10; i++) {
        setKey(Action_STATE & 1<<i, Action_Emulation_Keys[i], Action_flag[i]);
      }
    }

  }
  Action_LAST = Action_STATE;
}

// Message Handler
          if (Action_Ctrl_Con) {
            bool Action_Dspl_b[10] = {};
            for (int i = 0; i < 10; i++) {
              Action_Dspl_b[i] = (myAG.is_action_activated(AG_List[i]));
            }
            for (int i = 0; i < 8; i++) {
              bitWrite(Action_Dspl[0], i, Action_Dspl_b[i]);
            }
            for (int i = 0; i < 2; i++) {
              bitWrite(Action_Dspl[1], i, Action_Dspl_b[i+8]);
            }
          }

// Keyboard Emulation
  #define Action_Group_1                      '1'
  #define Action_Group_2                      '2'
  #define Action_Group_3                      '3'
  #define Action_Group_4                      '4'
  #define Action_Group_5                      '5'
  #define Action_Group_6                      '6'
  #define Action_Group_7                      '7'
  #define Action_Group_8                      '8'
  #define Action_Group_9                      '9'
  #define Action_Group_10                     '0'

// definitions
  const uint8_t Action_Emulation_Keys[10] = {
    Action_Group_1,
    Action_Group_2,
    Action_Group_3,
    Action_Group_4,
    Action_Group_5,
    Action_Group_6,
    Action_Group_7,
    Action_Group_8,
    Action_Group_9,
    Action_Group_10,
  };