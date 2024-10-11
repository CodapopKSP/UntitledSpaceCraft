//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Stage_Con = (sendHandshake(Stage_)!=255);
  Abort_Con = (sendHandshake(Abort_)!=255);
  Stage_Abort_Con = (sendHandshake(Stage_Abort_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Stage_Con) {module_transmission(Stage_, 0, 1, 0, stageB, 0, DummyFlag);}
  if (Abort_Con) {module_transmission(Abort_, 0, 1, 0, abortB, 0, DummyFlag);}
  if (Stage_Abort_Con) {module_transmission(Stage_Abort_, 0, 1, 0, Stage_Abort, 0, DummyFlag);}
}

void actions() {
  if (Stage_Con or Abort_Con or Stage_Abort_Con){Stage_Action();}
}
