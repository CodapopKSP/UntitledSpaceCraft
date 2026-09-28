//|-------------------------------|
//|       System Functions        |
//|-------------------------------|

void registerMessageChannels() {
  mySimpit.inboundHandler(messageHandler);

  mySimpit.registerChannel(LF_MESSAGE);
  mySimpit.registerChannel(OX_MESSAGE);
  mySimpit.registerChannel(SF_MESSAGE);
  mySimpit.registerChannel(ELECTRIC_MESSAGE);
  mySimpit.registerChannel(XENON_GAS_MESSAGE);
  mySimpit.registerChannel(MONO_MESSAGE);

  mySimpit.registerChannel(APSIDES_MESSAGE);
  mySimpit.registerChannel(APSIDESTIME_MESSAGE);

  mySimpit.registerChannel(ALTITUDE_MESSAGE);
  mySimpit.registerChannel(VELOCITY_MESSAGE);
  mySimpit.registerChannel(DELTAV_MESSAGE);

  mySimpit.registerChannel(ORBIT_MESSAGE);
  mySimpit.registerChannel(MANEUVER_MESSAGE);
}


byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void checkConnections() {
  LCD_Con = (sendHandshake(LCD_)!=255);
  mySimpit.printToKSP(String(LCD_Con), PRINT_TO_SCREEN);
}

void transmissions() {
  //ctrl_address, dspl_address, in_bytes, out_bytes, ctrl[], dspl[]
  if (LCD_Con) {LCD_transmission(LCD_, LCD_data);}
}

void actions() {
  //if (LCD_Con){LCD_Action();}
}
