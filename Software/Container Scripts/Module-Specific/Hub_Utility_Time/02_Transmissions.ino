//|-------------------|
//|   Transmissions   |
//|-------------------|

void module_transmission(int ctrl_address, int dspl_address, int in_bytes, int out_bytes, byte ctrl[], byte dspl[]) {
  // Control
  if (ctrl_address != 0) {
    Wire.requestFrom(ctrl_address, in_bytes);
    for (int i = 0; i < in_bytes; i++) {
      ctrl[i] = Wire.read();
    }
  }

  // Display
  if (dspl_address != 0) {
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
  }
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
    case EVA_MESSAGE:
      if (Util_Time_Ctrl_Con and On_EVA) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myEVA;
          myEVA = parseResource(msg);
          if (myEVA.available) {
            int myEVA_available = myEVA.available * 100.00;
            int myEVA_total = myEVA.total * 100.00;
            EVA_Dspl[0] = map(myEVA_available, 0, myEVA_total, 1, 10);
            if (myEVA_available==0) {
              EVA_Dspl[0] = 0;
            }
          }
        }
      }
      break;
      
    case FLIGHT_STATUS_MESSAGE:
      if (msgSize == sizeof(flightStatusMessage)) {
        flightStatusMessage myFS;
        myFS = parseFlightStatusMessage(msg);
        On_EVA = (myFS.flightStatusFlags & FLIGHT_IS_EVA);
      }
      break;
  }
}
