//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(EVA_MESSAGE);
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE);
}

void allZero() {
  if (Util_Time_Ctrl_Con) {
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
  Util_Time_Ctrl_Con = (sendHandshake(Util_Time_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Util_Time_Ctrl_Con) {module_transmission(Util_Time_Ctrl_, EVA_Dspl_, 1, 1, Util_Time_Ctrl, EVA_Dspl);}
}

void actions() {
  if (Util_Time_Ctrl_Con){Util_Time_Action();}
}
