//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(CAGSTATUS_MESSAGE);
}

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Action_Ctrl_Con = (sendHandshake(Action_Ctrl_)!=255);
  Action2_Ctrl_Con = (sendHandshake(Action2_Ctrl_)!=255);
  Action3_Ctrl_Con = (sendHandshake(Action3_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Action_Ctrl_Con) {module_transmission(Action_Ctrl_, Action_Dspl_, 2, 2, Action_Ctrl, Action_Dspl, AG_Update);}
  if (Action2_Ctrl_Con) {module_transmission(Action2_Ctrl_, Action2_Dspl_, 2, 2, Action2_Ctrl, Action2_Dspl, AG2_Update);}
  if (Action3_Ctrl_Con) {module_transmission(Action3_Ctrl_, Action3_Dspl_, 2, 2, Action3_Ctrl, Action3_Dspl, AG3_Update);}
}

void actions() {
  if (Action_Ctrl_Con){Action_Action();}
  if (Action2_Ctrl_Con){Action2_Action();}
  if (Action3_Ctrl_Con){Action3_Action();}
}
