//|-------------------|
//|      Actions      |
//|-------------------|

void Stage_Action() {
  if (Stage_Con) {
    Stage_Abort[0] = stageB[0] + abortB[0];
  }
  // Stage Button
  if (Stage_Abort[0] != Stage_Abort_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Stage_Abort[0] != Stage_Abort_STATE) {
    Stage_Abort_STATE = Stage_Abort[0];
    if (Stage_Abort_STATE & 1) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (Stage_Abort_STATE & 2) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  Stage_Abort_LAST = Stage_Abort_STATE;
}
