//|-------------------|
//|      Actions      |
//|-------------------|

void Time_Action() {
  if (Time_Ctrl[0] != Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Time_Ctrl[0] != Time_STATE) {
    Time_STATE = Time_Ctrl[0];

    for (int i = 1; i < 7; i++) {
      if (Time_STATE & 1<<i) {
        if (i > 1) {
          KEY.keyCode = Time_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        } else {
          mySimpit.send(TIMEWARP_MESSAGE, TIMEW);
        }
      }
    }

    // Phys Warp
    if (Time_STATE & 1) {
      KEY.keyCode = Time_List[0];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if ((Time_STATE & 128) and !F9_press) {
      KEY.keyCode = Time_List[7];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = true;
    }
    if (!(Time_STATE & 128) and F9_press) {
      KEY.keyCode = Time_List[7];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = false;
      KEY.modifier = 0;
    }
  }
  Time_LAST = Time_STATE;
}
