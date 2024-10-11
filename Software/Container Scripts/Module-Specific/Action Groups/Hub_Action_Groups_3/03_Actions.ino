//|-------------------|
//|      Actions      |
//|-------------------|

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
  mySimpit.deregisterChannel(CAGSTATUS_MESSAGE);
  mySimpit.registerChannel(CAGSTATUS_MESSAGE);
}
