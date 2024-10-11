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
  //mySimpit.deregisterChannel(CAGSTATUS_MESSAGE);
  //mySimpit.registerChannel(CAGSTATUS_MESSAGE);
}
