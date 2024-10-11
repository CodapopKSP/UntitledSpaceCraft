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
  EA_Control_Ctrl_Con = (sendHandshake(EA_Control_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (EA_Control_Ctrl_Con) {module_transmission(EA_Control_Ctrl_, EA_Control_Dspl_, 1, 1, EA_Control_Ctrl, EA_Control_Dspl, DummyFlag);}
}

void actions() {
  if (EA_Control_Ctrl_Con){EA_Control_Action();}
}
