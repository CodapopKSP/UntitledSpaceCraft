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
  if ((dspl_address != 0) and (UpdateFlag)) {
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
    UpdateFlag = false;
  }
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
    case SAS_MODE_INFO_MESSAGE:
      if (msgSize == sizeof(SASInfoMessage)) {
        SASInfoMessage mySAS;
        mySAS = parseSASInfoMessage(msg);
        Ctrl_Sys_Dspl[0] = mySAS.currentSASMode;
      }
      Ctrl_Sys_Update = true;
      break;

    case ACTIONSTATUS_MESSAGE:
      if (msgSize == 1) {
        currentActionStatus = msg[0];
      }
      Ctrl_Sys_Update = true;
      break;
  }
}
