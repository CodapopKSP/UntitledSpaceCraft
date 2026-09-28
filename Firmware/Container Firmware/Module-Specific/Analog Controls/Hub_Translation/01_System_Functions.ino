//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Translation_Con = (sendHandshake(Translation_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Translation_Con) {module_transmission(Translation_, 0, 9, 0, Translation, 0);}
}

void actions() {
  if (Translation_Con){Translation_Action();}
}
