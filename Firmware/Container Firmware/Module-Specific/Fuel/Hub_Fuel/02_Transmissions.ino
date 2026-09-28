//|-------------------|
//|   Transmissions   |
//|-------------------|

void module_transmission(int ctrl_address, int dspl_address, int in_bytes, int out_bytes, byte ctrl[], byte dspl[]) {
  // Control
  if (ctrl_address != 0) {
    mySimpit.printToKSP("transmitting 3");
    Wire.requestFrom(ctrl_address, in_bytes);
    for (int i = 0; i < in_bytes; i++) {
      ctrl[i] = Wire.read();
    }
  }

  // Display
  if (dspl_address != 0) {
    mySimpit.printToKSP("transmitting 2");
    Wire.beginTransmission(dspl_address);
    for (int i = 0; i < out_bytes; i++) {
      Wire.write(dspl[i]);
    }
    Wire.endTransmission();
  }
}

void fuel_transmission(int ctrl_address, int dspl_address, byte fuel_register[], byte stage_register[]) {
  mySimpit.printToKSP("transmitting");
  /*
  Wire.requestFrom(ctrl_address, 2);
  int mode = Wire.read();
  int brightness = Wire.read();*/

  int mode = 0;
  byte brightness = 0;
  constrain(mode, 0, 1);
  constrain(brightness, 0, 15);

  if (mode) {
    fuel_register[0] = stage_register[0];
    fuel_register[1] = stage_register[1];
    fuel_register[2] = stage_register[2];
    fuel_register[4] = stage_register[4];
  }

  for (int i = 0; i < 6; i++) {
    constrain(fuel_register[i], 0, 20);
  }
  
  Wire.beginTransmission(dspl_address);
  Wire.write(fuel_register[0]);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  /*
  Wire.write(fuel_register[1]);
  Wire.write(fuel_register[2]);
  Wire.write(fuel_register[3]);
  Wire.write(fuel_register[4]);
  Wire.write(fuel_register[5]);*/
  /*
  for (int i = 0; i < 6; i++) {
    Wire.write(fuel_register[i]);
  }*/
  Wire.write(brightness);
  Wire.endTransmission();
  mySimpit.printToKSP("transmitting end");
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
//==================================================================================================    
    
    case SF_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage mySF;
        mySF = parseResource(msg);
        if (mySF.available) {
          fuel_resources[0] = map(mySF.available, 0, mySF.total, 0, 20);
        } else {
          fuel_resources[0] = 0;
        }
        mySimpit.printToKSP("SF " + String(mySF.available) + " " + String(mySF.total));
      }
      mySimpit.printToKSP("transmit end");
      break;

    case LF_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myLF;
        myLF = parseResource(msg);
        if (myLF.available) {
          fuel_resources[1] = map(myLF.available, 0, myLF.total, 0, 20);
        } else {
          fuel_resources[1] = 0;
        }
        mySimpit.printToKSP("LF " + String(myLF.available) + " " + String(myLF.total));
      }
      mySimpit.printToKSP("transmit end");
      break;
    
    case OX_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myOX;
        myOX = parseResource(msg);
        if (myOX.available) {
          fuel_resources[2] = map(myOX.available, 0, myOX.total, 0, 20);
        } else {
          fuel_resources[2] = 0;
        }
        mySimpit.printToKSP("OX " + String(myOX.available) + " " + String(myOX.total));
      }
      mySimpit.printToKSP("transmit end");
      break;
    
    case MONO_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myMP;
        myMP = parseResource(msg);
        if (myMP.available) {
          fuel_resources[3] = map(myMP.available, 0, myMP.total, 0, 20);
        } else {
          fuel_resources[3] = 0;
        }
        mySimpit.printToKSP("MP " + String(myMP.available) + " " + String(myMP.total));
      }
      mySimpit.printToKSP("transmit end");
      break;
    
    case XENON_GAS_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myXE;
        myXE = parseResource(msg);
        if (myXE.available) {
          fuel_resources[4] = map(myXE.available, 0, myXE.total, 0, 20);
        } else {
          fuel_resources[4] = 0;
        }
        mySimpit.printToKSP("XE " + String(myXE.available) + " " + String(myXE.total));
      }
      mySimpit.printToKSP("transmit end");
      break;

    case ELECTRIC_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myEC;
        myEC = parseResource(msg);
        if (myEC.available) {
          fuel_resources[5] = map(myEC.available, 0, myEC.total, 0, 20);
        } else {
          fuel_resources[5] = 0;
        }
        mySimpit.printToKSP("EC " + String(myEC.available) + " " + String(myEC.total));
      }
      mySimpit.printToKSP("transmit end");
      break;

//==================================================================================================  

    case SF_STAGE_MESSAGE:
      mySimpit.printToKSP("transmit start");
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage mySF;
        mySF = parseResource(msg);
        if (mySF.available) {
          fuel_resources_stage[0] = map(mySF.available, 0, mySF.total, 0, 20);
        } else {
          fuel_resources_stage[0] = 0;
        }
      }
      mySimpit.printToKSP("transmit end");
      break;

    case LF_STAGE_MESSAGE:
      mySimpit.printToKSP("transmit start");
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myLF;
        myLF = parseResource(msg);
        if (myLF.available) {
          fuel_resources_stage[1] = map(myLF.available, 0, myLF.total, 0, 20);
        } else {
          fuel_resources_stage[1] = 0;
        }
      }
      mySimpit.printToKSP("transmit end");
      break;
    
    case OX_STAGE_MESSAGE:
      mySimpit.printToKSP("transmit start");
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myOX;
        myOX = parseResource(msg);
        if (myOX.available) {
          fuel_resources_stage[2] = map(myOX.available, 0, myOX.total, 0, 20);
        } else {
          fuel_resources_stage[2] = 0;
        }
      }
      mySimpit.printToKSP("transmit end");
      break;
    
    case XENON_GAS_STAGE_MESSAGE:
      mySimpit.printToKSP("transmit start");
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myXE;
        myXE = parseResource(msg);
        if (myXE.available) {
          fuel_resources_stage[4] = map(myXE.available, 0, myXE.total, 0, 20);
        } else {
          fuel_resources_stage[4] = 0;
        }
      }
      mySimpit.printToKSP("transmit end");
      break;
  }
}
