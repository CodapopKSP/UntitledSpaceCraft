//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(EVA_MESSAGE);
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE);
}

void allZero() {
  if (EVA_Ctrl_Con) {
    Wire.beginTransmission(EVA_Dspl_);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }
}


byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  EVA_Ctrl_Con = (sendHandshake(EVA_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (EVA_Ctrl_Con) {module_transmission(EVA_Ctrl_, EVA_Dspl_, 2, 1, EVA_Ctrl, EVA_Dspl);}
}

void actions() {
  if (EVA_Ctrl_Con and On_EVA){EVA_Action();}
}
