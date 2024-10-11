//|-------------------|
//|      Actions      |
//|-------------------|

void Util_Time_Action() {
  if (Util_Time_Ctrl[0] != Util_Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Util_Time_Ctrl[0] != Util_Time_STATE) {
    Util_Time_STATE = Util_Time_Ctrl[0];

    if (On_EVA) {
      for (int i = 0; i < 5; i++) {
        if (Util_Time_STATE & 1<<i) {
          KEY.keyCode = Util_Time_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        }
      }
    }
    if((Util_Time_STATE & 1<<5) and !F9_press){
      KEY.keyCode = Util_Time_List[5];
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      F9_press = true;
    }
    if(!(Util_Time_STATE & 1<<5) and F9_press){
      KEY.keyCode = Util_Time_List[5];
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      F9_press = false;
    }
    if (Util_Time_STATE & 1<<6) {
      KEY.keyCode = Util_Time_List[5];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Util_Time_STATE & 1<<7) {
      KEY.keyCode = Util_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    
  }
  Util_Time_LAST = Util_Time_STATE;
}
