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
    mySimpit.printToKSP("S LED");
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
    UpdateFlag = false;
    mySimpit.printToKSP("E LED");
  }
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
    case CAGSTATUS_MESSAGE:
      if (msgSize == sizeof(cagStatusMessage)) {
        mySimpit.printToKSP("S AGU");
        cagStatusMessage myAG;
        myAG = parseCAGStatusMessage(msg);
        bool Action_Dspl_b[10] = {};
        for (int i = 0; i < 10; i++) {
          Action_Dspl_b[i] = (myAG.is_action_activated(AG_List[i]));
        }
        for (int i = 0; i < 8; i++) {
          bitWrite(Action_Dspl[0], i, Action_Dspl_b[i]);
        }
        for (int i = 0; i < 2; i++) {
          bitWrite(Action_Dspl[1], i, Action_Dspl_b[i+8]);
        }
        bool Action2_Dspl_b[10] = {};
        for (int i = 0; i < 10; i++) {
          Action2_Dspl_b[i] = (myAG.is_action_activated(AG2_List[i]));
        }
        for (int i = 0; i < 8; i++) {
          bitWrite(Action2_Dspl[0], i, Action2_Dspl_b[i]);
        }
        for (int i = 0; i < 2; i++) {
          bitWrite(Action2_Dspl[1], i, Action2_Dspl_b[i+8]);
        }
        bool Action3_Dspl_b[10] = {};
        for (int i = 0; i < 10; i++) {
          Action3_Dspl_b[i] = (myAG.is_action_activated(AG3_List[i]));
        }
        for (int i = 0; i < 8; i++) {
          bitWrite(Action3_Dspl[0], i, Action3_Dspl_b[i]);
        }
        for (int i = 0; i < 2; i++) {
          bitWrite(Action3_Dspl[1], i, Action3_Dspl_b[i+8]);
        }
      }
      AG_Update = true;
      AG2_Update = true;
      AG3_Update = true;
      mySimpit.printToKSP("E AGU");
      break;
  }
}
