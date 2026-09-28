//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(SAS_MODE_INFO_MESSAGE);
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
}

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Ctrl_Sys_Ctrl_Con = (sendHandshake(Ctrl_Sys_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Ctrl_Sys_Ctrl_Con) {module_transmission(Ctrl_Sys_Ctrl_, Ctrl_Sys_Dspl_, 2, 1, Ctrl_Sys_Ctrl, Ctrl_Sys_Dspl, Ctrl_Sys_Update);}
}

void actions() {
  if (Ctrl_Sys_Ctrl_Con){Ctrl_Sys_Action();}
}
