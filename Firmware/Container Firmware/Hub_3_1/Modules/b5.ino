// Transmissions
if (Util_Time_Ctrl_Con) {module_transmission(Util_Time_Ctrl_, Util_Time_Ctrl, ONE_BYTE, EVA_Dspl_, EVA_Dspl, ONE_BYTE);}

// Enable Action
if (Util_Time_Ctrl_Con){Util_Time_Action();}

// Action Results
uint8_t Util_Time_List[8] = {
  'b',
  'f',
  ' ',
  'r',
  'u',
  KEY_F9,
  KEY_F5,
  KEY_ESC
};

// Action
void Util_Time_Action() {
  if (Util_Time_Ctrl[0] != Util_Time_STATE) {
    Util_Time_STATE = Util_Time_Ctrl[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (On_EVA) {
        for (int i = 0; i < 5; i++) {
          setSimpitAction(Util_Time_STATE & 1<<i, Util_Time_List[i], Util_Time_flag[i], tapKey);
        }
      }
      setSimpitAction_Switch(Util_Time_STATE & 1<<5, Util_Time_List[5], Util_Time_flag[5], tapKey, tapKey);
      setSimpitAction(Util_Time_STATE & 1<<6, Util_Time_List[6], Util_Time_flag[6], tapKey);
      setSimpitAction(Util_Time_STATE & 1<<7, Util_Time_List[7], Util_Time_flag[7], tapKey);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 7; i++) {
        setKey(Util_Time_STATE & 1<<i, Util_Time_Emulation_Keys[i], Util_Time_flag[i]);
      }
    }
  }
  Util_Time_LAST = Util_Time_STATE;
}

// Keyboard Emulation
  #define Utility_Time_Board                  'b'
  #define Utility_Time_Grab                   'f'
  #define Utility_Time_Jump                   ' '
  #define Utility_Time_Jet                    'r'
  #define Utility_Time_Light                  'u'
  #define Utility_Time_Pause                  KEY_ESC
  #define Utility_Time_Save                   KEY_F5
  #define Utility_Time_Load                   KEY_F9

// definitions
  const uint8_t Util_Time_Emulation_Keys[8] = {
    Utility_Time_Board,
    Utility_Time_Grab,
    Utility_Time_Jump,
    Utility_Time_Jet,
    Utility_Time_Light,
    Utility_Time_Load,
    Utility_Time_Save,
    Utility_Time_Pause,
  };