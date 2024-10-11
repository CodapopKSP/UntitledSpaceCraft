//|-------------------|
//|      Actions      |
//|-------------------|

void Navigation_Action() {
  if (Navigation[0] != Navigation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Navigation[0] != Navigation_STATE) {
    Navigation_STATE = Navigation[0];

    if (Navigation_STATE & 1) {
      KEY.keyCode = Nav_List[0];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 2) {
      KEY.keyCode = Nav_List[1];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 4) {
      KEY.keyCode = 0xA0;
      KEY.modifier = KEY_DOWN_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
      delay(50);

      KEY.keyCode = 0x09;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      delay(50);

      KEY.keyCode = 0xA0;
      KEY.modifier = KEY_UP_MOD;
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      KEY.modifier = 0;
    }
    if (Navigation_STATE & 8) {
      KEY.keyCode = Nav_List[3];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 16) {
      KEY.keyCode = Nav_List[4];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
    }
    if (Navigation_STATE & 32) {
      mySimpit.cycleNavBallMode();
    }
    
    if((Navigation_STATE & 64) && !MAP_on){
      KEY.keyCode = Nav_List[6];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = true;
      if (!NAV_on) {
        KEY.keyCode = Nav_List[7];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
    if(!(Navigation_STATE & 64) && MAP_on){
      KEY.keyCode = Nav_List[6];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      MAP_on = false;
      if (!NAV_on) {
        KEY.keyCode = Nav_List[7];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
    if((Navigation_STATE & 128) && !NAV_on){
      KEY.keyCode = Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      NAV_on = true;
    }
    if(!(Navigation_STATE & 128) && NAV_on){
      KEY.keyCode = Nav_List[7];
      mySimpit.send(KEYBOARD_EMULATOR, KEY);
      NAV_on = false;
    }
  }
  Navigation_LAST = Navigation_STATE;
}
