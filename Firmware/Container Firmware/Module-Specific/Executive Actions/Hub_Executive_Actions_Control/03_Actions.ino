//|-------------------|
//|      Actions      |
//|-------------------|

void EA_Control_Action() {
  int EA_Control_combinedBytes = EA_Control_Ctrl[0];
  if (EA_Control_combinedBytes != EA_Control_LAST) {
    lastDebounceTime_b = millis();
  }
  if (EA_Control_combinedBytes != EA_Control_STATE) {
    EA_Control_STATE = EA_Control_combinedBytes;

    if ((EA_Control_combinedBytes & 1) && !(currentActionStatus & LIGHT_ACTION)) {
      mySimpit.activateAction(LIGHT_ACTION);
    }
    if ((EA_Control_combinedBytes & 1) && (currentActionStatus & LIGHT_ACTION)) {
      mySimpit.deactivateAction(LIGHT_ACTION);
    }
    if ((EA_Control_combinedBytes & 2) && !(currentActionStatus & GEAR_ACTION)) {
      mySimpit.toggleAction(GEAR_ACTION);
    }
    if ((EA_Control_combinedBytes & 2) && (currentActionStatus & GEAR_ACTION)) {
      mySimpit.toggleAction(GEAR_ACTION);
    }
    
    // SAS/RCS
    if (EA_Control_combinedBytes & 4) {
      mySimpit.setSASMode(AP_STABILITYASSIST);
    }
    if((EA_Control_combinedBytes & 8) && !(currentActionStatus & SAS_ACTION)){
      mySimpit.activateAction(SAS_ACTION);
    }
    if(!(EA_Control_combinedBytes & 8) && (currentActionStatus & SAS_ACTION)){
      mySimpit.deactivateAction(SAS_ACTION);
    }
    if((EA_Control_combinedBytes & 16) && !(currentActionStatus & RCS_ACTION)){
      mySimpit.activateAction(RCS_ACTION);
    }
    if(!(EA_Control_combinedBytes & 16) && (currentActionStatus & RCS_ACTION)){
      mySimpit.deactivateAction(RCS_ACTION);
    }

    if (EA_Control_STATE & 32) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (EA_Control_STATE & 64) {
      mySimpit.activateAction(ABORT_ACTION);
    }
  }
  EA_Control_LAST = EA_Control_STATE;
}
