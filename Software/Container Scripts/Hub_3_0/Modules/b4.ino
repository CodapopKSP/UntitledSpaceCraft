// Transmissions
if (Util_Nav_Ctrl_Con) {module_transmission(Util_Nav_Ctrl_, Util_Nav_Ctrl, ONE_BYTE, EVA_Dspl_, EVA_Dspl, ONE_BYTE);}

// Enable Action
if (Util_Nav_Ctrl_Con){Util_Nav_Action();}

// Action Results
uint8_t Util_Nav_List[8] = {
  'b',
  'f',
  ' ',
  'r',
  'u',
  ']',
  0,
  'm'
};

// Action
void Util_Nav_Action() {
  if (Util_Nav_Ctrl[0] != Util_Nav_STATE) {
    Util_Nav_STATE = Util_Nav_Ctrl[0];
    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (On_EVA) {
        for (int i = 0; i < 5; i++) {
          setSimpitAction(Util_Nav_STATE & 1<<i, Util_Nav_List[i], Util_Nav_flag[i], tapKey);
        }
      }
      setSimpitAction(Util_Nav_STATE & 1<<5, Util_Nav_List[5], Util_Nav_flag[5], tapKey);
      setSimpitAction(Util_Nav_STATE & 1<<6, Util_Nav_List[6], Util_Nav_flag[6], simpitCycleNavBallMode);
      setSimpitAction_Switch(Util_Nav_STATE & 1<<7, Util_Nav_List[7], Util_Nav_flag[7], tapKey, tapKey);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 7; i++) {
        setKey(Util_Nav_STATE & 1<<i, Util_Nav_Emulation_Keys[i], Util_Nav_flag[i]);
      }
    }
  }
  Util_Nav_LAST = Util_Nav_STATE;
}

// Keyboard Emulation
  #define Utility_Board                       'b'
  #define Utility_Grab                        'f'
  #define Utility_Jump                        ' '
  #define Utility_Jet                         'r'
  #define Utility_Light                       'u'
  #define Utility_Map                         'm'
  #define Utility_Cycle_Ship                  ']'
  #define Utility_Cycle_Nav                   '1'

// definitions
  const uint8_t Util_Nav_Emulation_Keys[8] = {
    Utility_Board,
    Utility_Grab,
    Utility_Jump,
    Utility_Jet,
    Utility_Light,
    Utility_Cycle_Ship,
    Utility_Cycle_Nav,
    Utility_Map,
  };