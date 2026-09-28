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
  Action2_Ctrl_Con = (sendHandshake(Action2_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Action2_Ctrl_Con) {module_transmission(Action2_Ctrl_, Action2_Dspl_, 2, 2, Action2_Ctrl, Action2_Dspl, AG2_Update);}
}

void actions() {
  if (Action2_Ctrl_Con){Action2_Action();}
}
