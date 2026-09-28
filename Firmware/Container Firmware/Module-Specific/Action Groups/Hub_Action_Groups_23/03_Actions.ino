//|-------------------|
//|      Actions      |
//|-------------------|

void Action_Action() {
  int Action_combinedBytes = Action_Ctrl[0] + (Action_Ctrl[1]*256);
  for (int i = 0; i < 10; i++) {
    if (Action_combinedBytes != Action_LAST) {
      lastDebounceTime_b = millis();
    }
    if (Action_combinedBytes != Action_STATE) {
      Action_STATE = Action_combinedBytes;
      for (int i = 0; i < 10; i++) {
        if (Action_STATE & 1<<i) {
          mySimpit.toggleCAG(AG_List[i]);
          mySimpit.printToKSP(String(AG_List[i]), PRINT_TO_SCREEN);
        }
      }
    }
    Action_LAST = Action_STATE;
  }
}

void Action2_Action() {
  int Action2_combinedBytes = Action2_Ctrl[0] + (Action2_Ctrl[1]*256);
  for (int i = 0; i < 10; i++) {
    if (Action2_combinedBytes != Action2_LAST) {
      lastDebounceTime_b = millis();
    }
    if (Action2_combinedBytes != Action2_STATE) {
      Action2_STATE = Action2_combinedBytes;
      for (int i = 0; i < 10; i++) {
        if (Action2_STATE & 1<<i) {
          mySimpit.toggleCAG(AG2_List[i]);
        }
      }
    }
    Action2_LAST = Action2_STATE;
  }
}

void Action3_Action() {
  int Action3_combinedBytes = Action3_Ctrl[0] + (Action3_Ctrl[1]*256);
  for (int i = 0; i < 10; i++) {
    if (Action3_combinedBytes != Action3_LAST) {
      lastDebounceTime_b = millis();
    }
    if (Action3_combinedBytes != Action3_STATE) {
      Action3_STATE = Action3_combinedBytes;
      for (int i = 0; i < 10; i++) {
        if (Action3_STATE & 1<<i) {
          mySimpit.toggleCAG(AG3_List[i]);
        }
      }
    }
    Action3_LAST = Action3_STATE;
  }
}
