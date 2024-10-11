//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE);
}

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Time_Ctrl_Con = (sendHandshake(Time_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Time_Ctrl_Con) {module_transmission(Time_Ctrl_, Time_Dspl_, 1, 1, Time_Ctrl, Time_Dspl);}
}

void actions() {
  if (Time_Ctrl_Con){Time_Action();}
}
