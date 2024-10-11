//|-------------------------------|
//|       System Functions        |
//|-------------------------------|



byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  Fuel_Ctrl_Con = true; //(sendHandshake(Fuel_Ctrl_)!=255);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (Fuel_Ctrl_Con) {fuel_transmission(Fuel_Ctrl_, Fuel_Dspl_, 0, 0);}
}
