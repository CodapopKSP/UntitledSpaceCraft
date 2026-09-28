//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Throttle_Con = (sendHandshake(Throttle_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Throttle_Con) {module_transmission(Throttle_, 0, 3, 0, Throttle, 0);}
}

void actions() {
  if (Throttle_Con){Throttle_Action();}
}
