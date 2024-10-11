//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Camera_Con = (sendHandshake(Camera_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Camera_Con) {module_transmission(Camera_, 0, 2, 0, Camera, 0);}
}

void actions() {
  if (Camera_Con){Camera_Action();}
}
