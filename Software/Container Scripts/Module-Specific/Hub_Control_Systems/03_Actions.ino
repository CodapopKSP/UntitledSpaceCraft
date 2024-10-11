//|-------------------|
//|      Actions      |
//|-------------------|

void Ctrl_Sys_Action() {
  ControlSys_combinedBytes = Ctrl_Sys_Ctrl[0] + (Ctrl_Sys_Ctrl[1]*256);
  if (ControlSys_combinedBytes != Ctrl_Sys_LAST) {
    lastDebounceTime_b = millis();
  }
  if (ControlSys_combinedBytes != Ctrl_Sys_STATE) {
    Ctrl_Sys_STATE = ControlSys_combinedBytes;
    for (int i = 0; i < 10; i++) {
      if (Ctrl_Sys_STATE & 1<<i) {
        mySimpit.setSASMode(SASMode[i]);
      }
    }
  }
  Ctrl_Sys_LAST = Ctrl_Sys_STATE;

  // SAS/RCS
  if((ControlSys_combinedBytes & 1024) && !(currentActionStatus & SAS_ACTION)){
    mySimpit.activateAction(SAS_ACTION);
  }
  if(!(ControlSys_combinedBytes & 1024) && (currentActionStatus & SAS_ACTION)){
    mySimpit.deactivateAction(SAS_ACTION);
  }
  if((ControlSys_combinedBytes & 2048) && !(currentActionStatus & RCS_ACTION)){
    mySimpit.activateAction(RCS_ACTION);
  }
  if(!(ControlSys_combinedBytes & 2048) && (currentActionStatus & RCS_ACTION)){
    mySimpit.deactivateAction(RCS_ACTION);
  }

  mySimpit.deregisterChannel(SAS_MODE_INFO_MESSAGE);
  mySimpit.registerChannel(SAS_MODE_INFO_MESSAGE);
  mySimpit.deregisterChannel(ACTIONSTATUS_MESSAGE);
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
}
