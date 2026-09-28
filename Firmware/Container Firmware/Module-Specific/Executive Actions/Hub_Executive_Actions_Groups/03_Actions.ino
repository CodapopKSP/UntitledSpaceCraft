//|-------------------|
//|      Actions      |
//|-------------------|

void EA_Groups_Action() {
  int EA_Groups_combinedBytes = EA_Groups_Ctrl[0];
  if (EA_Groups_combinedBytes != EA_Groups_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EA_Groups_combinedBytes != EA_Groups_STATE) {
    EA_Groups_STATE = EA_Groups_combinedBytes;
    for (int i = 0; i < 5; i++) {
      if (EA_Groups_STATE & 1<<i) {
        mySimpit.toggleCAG(i+1);
        mySimpit.printToKSP(String(i), PRINT_TO_SCREEN);
      }
    }
    if (EA_Groups_STATE & 32) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (EA_Groups_STATE & 64) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  EA_Groups_LAST = EA_Groups_STATE;
}
