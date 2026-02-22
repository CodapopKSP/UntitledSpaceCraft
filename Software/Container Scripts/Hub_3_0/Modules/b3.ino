// Transmissions
if (Navigation_Time_Ctrl_Con) {module_transmission(Navigation_Time_Ctrl_, Navigation_Time_Ctrl, ONE_BYTE, Time_Dspl_, Time_Dspl, ONE_BYTE);}

// Enable Action
if (Navigation_Time_Ctrl_Con){Navigation_Time_Action();}

// Action Results
uint8_t Navigation_Time_List[8] = {
  KEY_LEFT_ALT,
  '1',
  '.',
  ',',
  '/',
  ']',
  '`',
  'm'
};

// Action
void Navigation_Time_Action() {
  if (Navigation_Time_Ctrl[0] != Navigation_Time_STATE) {
    Navigation_Time_STATE = Navigation_Time_Ctrl[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setKey(Navigation_Time_STATE & 1, Navigation_Time_List[0], Navigation_Time_flag[0]);
      setSimpitAction(Navigation_Time_STATE & 2, 0, Navigation_Time_flag[1], simpitSendTimewarp);
      for (int i = 2; i <= 6; i++) {
        setSimpitAction(Navigation_Time_STATE & 1<<i, Navigation_Time_List[i], Navigation_Time_flag[i], tapKey);
      }
      setSimpitAction_Switch(Navigation_Time_STATE & 128, Navigation_Time_List[7], Navigation_Time_flag[7], tapKey, tapKey);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 7; i++) {
        setKey(Navigation_Time_STATE & 1<<i, Navigation_Time_Emulation_Keys[i], Navigation_Time_flag[i]);
      }
      setKey_Switch(Navigation_Time_STATE & 128, Navigation_Map, Navigation_Time_flag[7]);
    }
  }
  Navigation_Time_LAST = Navigation_Time_STATE;
}

// Keyboard Emulation
  #define Navigation_Time_Map                 'm'
  #define Navigation_Time_Map_Return          '`'
  #define Navigation_Time_Cycle_Ship_Up       ']'
  #define Navigation_Time_To_Mnvr             '1'
  #define Navigation_Time_Phys_Tw             KEY_LEFT_ALT
  #define Navigation_Time_Timewarp_Up         '.'
  #define Navigation_Time_Timewarp_Down       ','
  #define Navigation_Time_Stop_Tw             '/'

// definitions
  const uint8_t Navigation_Time_Emulation_Keys[8] = {
    Navigation_Time_Phys_Tw,
    Navigation_Time_To_Mnvr,
    Navigation_Time_Timewarp_Up,
    Navigation_Time_Timewarp_Down,
    Navigation_Time_Stop_Tw,
    Navigation_Time_Cycle_Ship_Up,
    Navigation_Time_Map_Return,
    Navigation_Time_Map,
  };