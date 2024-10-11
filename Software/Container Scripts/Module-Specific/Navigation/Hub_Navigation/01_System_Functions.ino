//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Navigation_Con = (sendHandshake(Navigation_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Navigation_Con) {module_transmission(Navigation_, 0, 1, 0, Navigation, 0);}
}

void actions() {
  if (Navigation_Con){Navigation_Action();} // ---------------------|||||||||||||||||  SCENE CHANGE LOGIC
}
