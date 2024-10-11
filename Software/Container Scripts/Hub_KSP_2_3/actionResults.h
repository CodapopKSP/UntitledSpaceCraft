//|-------------------|
//|      Results      |
//|-------------------|

  const int AG_List[10] = {1,6,2,7,3,8,4,9,5,10};
  const int AG2_List[10] = {11,16,12,17,13,18,14,19,15,20};
  const int AG3_List[10] = {21,26,22,27,23,28,24,29,25,30};
  const int EA_Groups_List[10] = {1, 2, 3, 4, 5};
  
  AutopilotMode SASMode[10] = {
    AP_MANEUVER,
    AP_STABILITYASSIST,
    AP_RETROGRADE,
    AP_PROGRADE,
    AP_ANTINORMAL,
    AP_NORMAL,
    AP_RADIALOUT,
    AP_RADIALIN,
    AP_ANTITARGET,
    AP_TARGET,
  };
  
  int Nav_List[8] = {
    0xC0, // `
    0xDB, // [
    0,    // NULL
    0xDD, // ]
    0x9,  // TAB
    0,    // NULL
    0x4D, // M
    0x6E, // .
  };

  const int Time_List[8] = {
    0x12, // ALT
    0,    // NULL
    0xBE, // .
    0xBC, // ,
    0xBF, // /
    0x1B, // ESC
    0x74, // F5
    0x78, // F9
  };

  const int EVA_List_Analog[11] = {
    0x42, // B
    0x46, // F
    0x20, // SPACE
    0x52, // R
    0xA0, // SHIFT
    0xA2, // CTRL
    0x57, // W
    0x41, // A
    0x53, // S
    0x44, // D
  };

  const int Camera_List[10] = {
    0x71, // F2
    0x70, // F1
    0x6D, // -
    0x27, // RIGHT
    0x28, // DOWN
    0x26, // UP.
    0x25, // LEFT
    0x6B, // +
    0x43, // C
    0x56, // V
  };

  const int EVA_List[12] = {
    0x42, // B
    0x46, // F
    0x20, // SPACE
    0x52, // R
    0x10, // SHIFT
    0xA2, // CTRL
    0x57, // W
    0x41, // A
    0x53, // S
    0x44, // D
    0x55,  // U
    0x50, // P
  };
  
  const int Navigation_Time_List[8] = {
    0x12, // ALT
    0x1B, // ESC
    0xBE, // .
    0xBC, // ,
    0xBF, // /
    0xDD, // ]
    0xC0, // `
    0x4D, // M
  };

  const int Util_Nav_List[11] = {
    0x42, // B
    0x46, // F
    0x20, // SPACE
    0x52, // R
    0x55, // U
    0xDD, // ]
    0,    // NULL
    0x4D, // M
  };

  const int Util_Time_List[11] = {
    0x42, // B
    0x46, // F
    0x20, // SPACE
    0x52, // R
    0x55, // U
    0x78, // F9
    0x74, // F5
    0x1B, // ESC
  };
