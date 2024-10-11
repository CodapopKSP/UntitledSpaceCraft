//|-------------------|
//|      Actions      |
//|-------------------|

void Camera_Action() {
  Camera_combinedBytes = Camera[0] + (Camera[1]*256);
  if (Camera_combinedBytes != Camera_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Camera_combinedBytes != Camera_STATE) {
    Camera_STATE = Camera_combinedBytes;

    for (int i = 0; i < 2; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }

    for (int i = 2; i < 8; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        KEY.modifier = KEY_DOWN_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      } else {
        KEY.keyCode = Camera_List[i];
        KEY.modifier = KEY_UP_MOD;
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
        KEY.modifier = 0;
      }
    }

    for (int i = 8; i < 10; i++) {
      if (Camera_STATE & 1<<i) {
        KEY.keyCode = Camera_List[i];
        mySimpit.send(KEYBOARD_EMULATOR, KEY);
      }
    }
  }
  Camera_LAST = Camera_STATE;
}
