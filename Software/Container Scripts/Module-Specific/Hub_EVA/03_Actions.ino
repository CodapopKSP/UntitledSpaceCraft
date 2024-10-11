//|-------------------|
//|      Actions      |
//|-------------------|

void EVA_Action() {
  EVA_combinedBytes = (EVA_Ctrl[1]*256) + EVA_Ctrl[0];
  if (EVA_combinedBytes != EVA_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EVA_combinedBytes != EVA_STATE) {
    EVA_STATE = EVA_combinedBytes;

    for (int i = 0; i < 4; i++) {
      if (EVA_STATE & 1<<i) {
        KEY.keyCode = EVA_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }

    for (int i = 4; i < 11; i++) {
      if (EVA_combinedBytes & 1<<i) {
        KEY.keyCode = EVA_List[i];
        KEY.modifier = KEY_DOWN_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      } else {
        KEY.keyCode = EVA_List[i];
        KEY.modifier = KEY_UP_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      }
    }
  }
  EVA_LAST = EVA_STATE;
}
