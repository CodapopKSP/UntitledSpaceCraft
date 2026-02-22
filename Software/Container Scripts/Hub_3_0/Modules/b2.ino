// Transmissions
if (Navigation_Con) {module_transmission(Navigation_, Navigation, ONE_BYTE, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Navigation_Con){Navigation_Action();}

// Action Results
uint8_t Nav_List[8] = {
  Nav_KSP1_KSP2,
  '[',
  KEY_TAB,
  ']',
  KEY_TAB,
  0,        // NULL
  'm',
  'y',      // Was Numpad .
};

// Action
void Navigation_Action() {
  if (Navigation[0] != Navigation_STATE) {
    Navigation_STATE = Navigation[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setSimpitAction(Navigation_STATE & 1, Nav_List[0], Navigation_flag[0], tapKey);
      setSimpitAction(Navigation_STATE & 2, Nav_List[1], Navigation_flag[1], tapKey);

      if (Navigation_STATE & 4) {
        Keyboard.press(KSP_MOD_KEY);
        delay(50);
        tapKey(Nav_List[2]);
        delay(50);
        Keyboard.release(KSP_MOD_KEY);
      }

      setSimpitAction(Navigation_STATE & 8, Nav_List[3], Navigation_flag[3], tapKey);
      setSimpitAction(Navigation_STATE & 16, Nav_List[4], Navigation_flag[4], tapKey);
      setSimpitAction(Navigation_STATE & 32, Nav_List[5], Navigation_flag[5], simpitCycleNavBallMode);

      if((Navigation_STATE & 64) && !Navigation_Map_flag){
        tapKey(Nav_List[6]);
        if (!Navigation_NAV_flag) {
          tapKey(Nav_List[7]);
        }
        Navigation_Map_flag = true;
      }
      if(!(Navigation_STATE & 64) && Navigation_Map_flag){
        tapKey(Nav_List[6]);
        if (!Navigation_NAV_flag) {
          tapKey(Nav_List[7]);
        }
        Navigation_Map_flag = false;
      }

      setSimpitAction_Switch(Navigation_STATE & 128, Nav_List[7], Navigation_NAV_flag, tapKey, tapKey);

    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 6; i++) {
        setKey(Navigation_STATE & 1<<i, Navigation_Emulation_Keys[i], Navigation_flag[i]);
      }
      setKey_Switch(Navigation_STATE & 64, Navigation_Nav, Navigation_flag[6]);
      setKey_Switch(Navigation_STATE & 128, Navigation_Map, Navigation_flag[7]);
    }
  }
  Navigation_LAST = Navigation_STATE;
}

// Keyboard Emulation
  #define Navigation_Map                      'm'
  #define Navigation_Cycle_Map_Up             KEY_TAB
  #define Navigation_Cycle_Map_Down           KEY_TAB
  #define Navigation_Map_Return               '`'
  #define Navigation_Nav                      '.'
  #define Navigation_Cycle_Nav                '1'
  #define Navigation_Cycle_Ship_Up            ']'
  #define Navigation_Cycle_Ship_Down          '['

// definitions
  const uint8_t Navigation_Emulation_Keys[8] = {
    Navigation_Map_Return,
    Navigation_Cycle_Ship_Up,
    Navigation_Cycle_Map_Up,
    Navigation_Cycle_Ship_Down,
    Navigation_Cycle_Map_Down,
    Navigation_Cycle_Nav,
    Navigation_Map,
    Navigation_Nav
  };