//|-------------------|
//|      Actions      |
//|-------------------|

void Util_Nav_Action() {
  if (Util_Nav_Ctrl[0] != Util_Nav_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Util_Nav_Ctrl[0] != Util_Nav_STATE) {
    Util_Nav_STATE = Util_Nav_Ctrl[0];

    if (On_EVA) {
      for (int i = 0; i < 5; i++) {
        if (Util_Nav_STATE & 1<<i) {
          KEY.keyCode = Util_Nav_List[i];
          mySimpit.send(KEYBOARD_EMULATOR, KEY);
        }
      }
    }
    if (Util_Nav_STATE & 1<<5) {
        KEY.keyCode = Util_Nav_List[5];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    if (Util_Nav_STATE & 1<<6) {
      mySimpit.cycleNavBallMode();
    }
    if((Util_Nav_STATE & 1<<7) && !MAP_on){
      KEY.keyCode = Util_Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
    }
    if(!(Util_Nav_STATE & 1<<7) && MAP_on){
      KEY.keyCode = Util_Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
    }
  }
  Util_Nav_LAST = Util_Nav_STATE;
}
