// Transmissions
if (Camera_Con) {module_transmission(Camera_, Camera, TWO_BYTES, NO_DISPLAY, NO_DISPLAY, NO_DISPLAY);}

// Enable Action
if (Camera_Con){Camera_Action();}

// Action Results
const int Camera_List[10] = {
  KEY_F2,
  KEY_F1,
  '-',      // Was Numpad -
  KEY_RIGHT_ARROW,
  KEY_DOWN_ARROW,
  KEY_UP_ARROW,
  KEY_LEFT_ARROW,
  '=',      // Was Numpad +
  'c',
  'v',
};

// Action
void Camera_Action() {
  Camera_combinedBytes = Camera[0] + (Camera[1]*256);
  if (Camera_combinedBytes != Camera_STATE) {
    Camera_STATE = Camera_combinedBytes;

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 2; i++) {
        setSimpitAction(Camera_STATE & 1<<i, Camera_List[i], Camera_flag[i], tapKey);
      }
      for (int i = 2; i < 8; i++) {
        setKey(Camera_STATE & 1<<i, Camera_List[i], Camera_flag[i]);
      }
      for (int i = 8; i < 10; i++) {
        setSimpitAction(Camera_STATE & 1<<i, Camera_List[i], Camera_flag[i], tapKey);
      }
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 10; i++) {
        setKey(Camera_STATE & 1<<i, Camera_Emulation_Keys[i], Camera_flag[i]);
      }
    }
  }
  Camera_LAST = Camera_STATE;
}

// Keyboard Emulation
  #define Camera_UI                           KEY_F2
  #define Camera_Screenshot                   KEY_F1
  #define Camera_Minus                        '-'
  #define Camera_Right                        KEY_RIGHT_ARROW
  #define Camera_Down                         KEY_DOWN_ARROW
  #define Camera_Left                         KEY_LEFT_ARROW
  #define Camera_Up                           KEY_UP_ARROW
  #define Camera_Plus                         '+'
  #define Camera_IVA                          'c'
  #define Camera_CycleCamera                  'v'

// definitions
  const uint8_t Camera_Emulation_Keys[10] = {
    Camera_UI,
    Camera_Screenshot,
    Camera_Minus,
    Camera_Right,
    Camera_Down,
    Camera_Left,
    Camera_Up,
    Camera_Plus,
    Camera_IVA,
    Camera_CycleCamera,
  };