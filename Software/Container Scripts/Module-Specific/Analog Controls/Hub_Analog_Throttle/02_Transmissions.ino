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
    case ACTIONSTATUS_MESSAGE:
      if (msgSize == 1) {
        currentActionStatus = msg[0];
      }
      break;
  }
}
