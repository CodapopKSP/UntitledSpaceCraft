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
  Navigation_Time_Ctrl_Con = (sendHandshake(Navigation_Time_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Navigation_Time_Ctrl_Con) {module_transmission(Navigation_Time_Ctrl_, Time_Dspl_, 1, 1, Navigation_Time_Ctrl, Time_Dspl);
}

void actions() {
  if (Navigation_Time_Ctrl_Con){Navigation_Time_Action();}
}
