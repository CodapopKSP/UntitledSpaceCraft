//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
}

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Rotation_Con = (sendHandshake(Rotation_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Rotation_Con) {module_transmission(Rotation_, 0, 7, 0, Rotation, 0);}
}

void actions() {
  if (Rotation_Con){Rotation_Action();}
}
