//|-------------------|
//|   Transmissions   |
//|-------------------|

void module_transmission(int ctrl_address, int dspl_address, int in_bytes, int out_bytes, byte ctrl[], byte dspl[], bool &UpdateFlag) {
  // Control
  if (ctrl_address != 0) {
    Wire.requestFrom(ctrl_address, in_bytes);
    for (int i = 0; i < in_bytes; i++) {
      ctrl[i] = Wire.read();
    }
  }

  // Display
  if ((dspl_address != 0)) {// and (UpdateFlag)) {
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
    if (dspl_address == Ctrl_Sys_Dspl_) {
      Wire.beginTransmission(dspl_address);
      for (int i = 0; i < out_bytes; i++) {
        Wire.write(dspl[i]);
      }
      Wire.endTransmission();
    }
    UpdateFlag = false;
  }
}

void LCD_transmission(int dspl_address, String LCD_data_register[]) {
  if (LCD_transmit == 0) {
    Wire.beginTransmission(dspl_address);
    Wire.write(LCD_transmit);
    sendPacket(LCD_data_register[0]);
    sendPacket(LCD_data_register[1]);
    sendPacket(LCD_data_register[2]);
    Wire.endTransmission();
    LCD_transmit = 1;
  } else if (LCD_transmit == 1) {
    Wire.beginTransmission(dspl_address);
    Wire.write(LCD_transmit);
    sendPacket(LCD_data_register[3]);
    sendPacket(LCD_data_register[4]);
    sendPacket(LCD_data_register[5]);
    Wire.endTransmission();
    LCD_transmit = 2;
  } else if (LCD_transmit == 2) {
    Wire.beginTransmission(dspl_address);
    Wire.write(LCD_transmit);
    sendPacket(LCD_data_register[6]);
    sendPacket(LCD_data_register[7]);
    sendPacket(LCD_data_register[8]);
    sendPacket(LCD_data_register[9]);
    Wire.endTransmission();
    LCD_transmit = 3;
  } else {
    byte LCD_mode_incoming;
    Wire.requestFrom(dspl_address, 1);
    LCD_mode_incoming = Wire.read();
    LCD_transmit = 0;
    if (LCD_mode_incoming != LCD_mode) {
      LCD_mode = LCD_mode_incoming;
    }
  }
}

void sendPacket(String dataLCD) {
  uint16_t packet_size = dataLCD.length();
  if (isnan(packet_size)) {
    packet_size = 3; // set value to zero if it is not a valid number
  }
  Wire.write(packet_size);
  Wire.write(dataLCD.c_str(), packet_size);
}
