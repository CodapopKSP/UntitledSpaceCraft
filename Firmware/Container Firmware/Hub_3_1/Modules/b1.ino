// Transmissions  
if (Time_Ctrl_Con) {module_transmission(Time_Ctrl_, Time_Ctrl, ONE_BYTE, Time_Dspl_, Time_Dspl, ONE_BYTE);}

// Enable Action
if (Time_Ctrl_Con){Time_Action();}

// Action Results
uint8_t Time_List[8] = {
  KSP_MOD_KEY2,
  0,        // NULL
  '.',
  ',',
  '/',
  KEY_ESC,
  KEY_F5,
  KEY_F9,
};

// Action
void Time_Action() {
  if (Time_Ctrl[0] != Time_STATE) {
    Time_STATE = Time_Ctrl[0];

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      setKey(Time_STATE & 1, Time_List[0], Time_flag[0]);
      setSimpitAction(Time_STATE & 2, 0, Time_flag[1], simpitSendTimewarp);
      for (int i = 2; i < 7; i++) {
        setSimpitAction(Time_STATE & 1<<i, Time_List[i], Time_flag[i], tapKey);
      }
      setKey(Time_STATE & 128, Time_List[7], Time_flag[7]);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 8; i++) {
        setKey(Time_STATE & 1<<i, Time_Emulation_Keys[i], Time_flag[i]);
      }
    }
  }
  Time_LAST = Time_STATE;
}

// Keyboard Emulation
  #define Time_Phys_Tw                        'p'
  #define Time_To_Mnvr                        '1'
  #define Time_Timewarp_Up                    '.'
  #define Time_Timewarp_Down                  ','
  #define Time_Stop_Tw                        '/'
  #define Time_Pause                          'e'
  #define Time_Save                           's'
  #define Time_Load                           'l'

// definitions
  const uint8_t Time_Emulation_Keys[8] = {
    Time_Phys_Tw,
    Time_To_Mnvr,
    Time_Timewarp_Up,
    Time_Timewarp_Down,
    Time_Stop_Tw,
    Time_Pause,
    Time_Save,
    Time_Load
  };