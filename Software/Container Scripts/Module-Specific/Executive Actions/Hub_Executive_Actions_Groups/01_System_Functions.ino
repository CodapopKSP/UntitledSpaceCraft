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
  EA_Groups_Ctrl_Con = (sendHandshake(EA_Groups_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (EA_Groups_Ctrl_Con) {module_transmission(EA_Groups_Ctrl_, EA_Groups_Dspl_, 1, 1, EA_Groups_Ctrl, EA_Groups_Dspl, AG_Update);}
}

void actions() {
  if (EA_Groups_Ctrl_Con){EA_Groups_Action();}
}
