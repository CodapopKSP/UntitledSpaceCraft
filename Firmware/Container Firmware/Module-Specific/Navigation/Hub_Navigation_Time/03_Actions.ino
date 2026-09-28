//|-------------------|
//|      Actions      |
//|-------------------|

void Navigation_Time_Action() {
  if (Navigation_Time_Ctrl[0] != Navigation_Time_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation_Time_Ctrl[0] != Navigation_Time_STATE) {
    Navigation_Time_STATE = Navigation_Time_Ctrl[0];

    for (int i = 1; i < 7; i++) {
      if (Navigation_Time_STATE & 1<<i) {
        KEY.keyCode = Navigation_Time_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }

    // Phys Warp
    if (Navigation_Time_STATE & 1) {
      KEY.keyCode = Navigation_Time_List[0];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if((Navigation_Time_STATE & 128) && !MAP_on){
      KEY.keyCode = Navigation_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
    }
    if(!(Navigation_Time_STATE & 128) && MAP_on){
      KEY.keyCode = Navigation_Time_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
    }
  }
  Navigation_Time_LAST = Navigation_Time_STATE;
}
