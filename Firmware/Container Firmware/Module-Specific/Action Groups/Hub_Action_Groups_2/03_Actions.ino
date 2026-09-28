//|-------------------|
//|      Actions      |
//|-------------------|

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
  mySimpit.deregisterChannel(CAGSTATUS_MESSAGE);
  mySimpit.registerChannel(CAGSTATUS_MESSAGE);
}
