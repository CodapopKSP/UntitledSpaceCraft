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
    UpdateFlag = false;
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
    mySimpit.printToKSP("Display Complete", PRINT_TO_SCREEN);
  }
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
    case CAGSTATUS_MESSAGE:
      if (msgSize == sizeof(cagStatusMessage)) {
        cagStatusMessage myAG;
        myAG = parseCAGStatusMessage(msg);
        bool EA_Groups_Dspl_b[8] = {0,0,0,0,0,0,0,0};
        for (int i = 0; i < 8; i++) {
          EA_Groups_Dspl_b[i] = (myAG.is_action_activated(i+1));
        }
        for (int i = 0; i < 8; i++) {
          bitWrite(EA_Groups_Dspl[0], i, EA_Groups_Dspl_b[i]);
        }
      }
      AG_Update = true;
      mySimpit.printToKSP("Message Complete", PRINT_TO_SCREEN);
      break;
  }
}
