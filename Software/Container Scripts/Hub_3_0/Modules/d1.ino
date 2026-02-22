// Transmissions
if (EVA_Ctrl_Con) {module_transmission(EVA_Ctrl_, EVA_Ctrl, TWO_BYTES, EVA_Dspl_, EVA_Dspl, ONE_BYTE);}

// Enable Action
if (EVA_Ctrl_Con){EVA_Action();}

// Action Results
uint8_t EVA_List[12] = {
  'b',
  'f',
  ' ',
  'r',
  KEY_LEFT_SHIFT,
  KEY_LEFT_CTRL,
  'w',
  'a',
  's',
  'd',
  'u',
  'p',
};

// Action
void EVA_Action() {
  EVA_combinedBytes = (EVA_Ctrl[1]*256) + EVA_Ctrl[0];
  if (EVA_combinedBytes != EVA_STATE) {
    EVA_STATE = EVA_combinedBytes;


    if (!keyboardEmulation) {
      // Controller is in KSP mode
      if (On_EVA) {
        for (int i = 0; i < 4; i++) {
          setSimpitAction(EVA_STATE & 1<<i, EVA_List[i], EVA_flag[i], tapKey);
        }
        for (int i = 4; i < 11; i++) {
          setSimpitAction_Switch(EVA_STATE & 1<<i, EVA_List[i], EVA_flag[i], tapKey, tapKey);
        }
        setSimpitAction((EVA_STATE & 1<<2) and (EVA_STATE & 1<<10), EVA_List[11], EVA_flag[11], tapKey);
      }
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 11; i++) {
        setKey(EVA_STATE & 1<<i, EVA_Emulation_Keys[i], EVA_flag[i]);
      }
    }
  }
  EVA_LAST = EVA_STATE;
}

// Message Handler
    case EVA_MESSAGE:
      if (EVA_Ctrl_Con || Util_Nav_Ctrl_Con || Util_Time_Ctrl_Con) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myEVA;
          myEVA = parseResource(msg);
          if (myEVA.available) {
            int myEVA_available = myEVA.available * 100.00;
            int myEVA_total = myEVA.total * 100.00;
            EVA_Dspl[0] = map(myEVA_available, 0, myEVA_total, 1, 10);
            if (myEVA_available==0) {
              EVA_Dspl[0] = 0;
            }
          }
        }
      }
      break;

// Keyboard Emulation
  #define EVA_Board                           'b'
  #define EVA_Grab                            'f'
  #define EVA_Jump                            ' '
  #define EVA_Jet                             'r'
  #define EVA_Light                           'u'
  #define EVA_Up                              KEY_LEFT_SHIFT
  #define EVA_Down                            KEY_LEFT_CTRL
  #define EVA_W                               'w'
  #define EVA_A                               'a'
  #define EVA_S                               's'
  #define EVA_D                               'd'

// definitions
  const uint8_t EVA_Emulation_Keys[11] = {
    EVA_Board,
    EVA_Grab,
    EVA_Jump,
    EVA_Jet,
    EVA_Up,
    EVA_Down,
    EVA_W,
    EVA_A,
    EVA_S,
    EVA_D,
    EVA_Light
  };