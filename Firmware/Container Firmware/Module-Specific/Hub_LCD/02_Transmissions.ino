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
      mySimpit.requestMessageOnChannel(0);
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

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
//==================================================================================================    
    case LF_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myLF;
          myLF = parseResource(msg);
          if (myLF.available) {
            LCD_data[0] = String(map(myLF.available, 0, myLF.total, 0, 52));
          } else {
            LCD_data[0] = "0";
          }
        }
      }
      break;
    
    case OX_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myOX;
          myOX = parseResource(msg);
          if (myOX.available) {
            LCD_data[1] = String(map(myOX.available, 0, myOX.total, 0, 52));
          } else {
            LCD_data[1] = "0";
          }
        }
      }
      break;

    case SF_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage mySF;
          mySF = parseResource(msg);
          if (mySF.available) {
            LCD_data[2] = String(map(mySF.available, 0, mySF.total, 0, 52));
          } else {
            LCD_data[2] = "0";
          }
        }
      }
      break;

    case ELECTRIC_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myEC;
          myEC = parseResource(msg);
          if (myEC.available) {
            LCD_data[3] = String(map(myEC.available, 0, myEC.total, 0, 52));
          } else {
            LCD_data[3] = "0";
          }
        }
      }
      break;

    case XENON_GAS_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myXE;
          myXE = parseResource(msg);
          if (myXE.available) {
            LCD_data[4] = String(map(myXE.available, 0, myXE.total, 0, 52));
          } else {
            LCD_data[4] = "0";
          }
        }
      }
      break;

    case MONO_MESSAGE:
      if (LCD_mode == 0) {
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage myMP;
          myMP = parseResource(msg);
          if (myMP.available) {
            LCD_data[5] = String(map(myMP.available, 0, myMP.total, 0, 52));
          } else {
            LCD_data[5] = "0";
          }
        }
      }
      break;

    case APSIDES_MESSAGE:
      if ((LCD_mode == 1) or (LCD_mode == 2) or (LCD_mode == 3)) {
        if (msgSize == sizeof(apsidesMessage)) {
          apsidesMessage myAps;
          myAps = parseMessage<apsidesMessage>(msg);
          String apo = String(myAps.apoapsis);
          String peri = String(myAps.periapsis);
          int stringLength = apo.length();
          apo.remove(stringLength - 3, 3);
          LCD_data[6] = apo;
          stringLength = peri.length();
          peri.remove(stringLength - 3, 3);
          LCD_data[7] = peri;
        }
      }
      break;

    case APSIDESTIME_MESSAGE:
      if ((LCD_mode == 1) or (LCD_mode == 2) or (LCD_mode == 3)) {
        if (msgSize == sizeof(apsidesTimeMessage)) {
          apsidesTimeMessage myAps;
          myAps = parseMessage<apsidesTimeMessage>(msg);
          String apo = String(myAps.apoapsis);
          String peri = String(myAps.periapsis);
          LCD_data[8] = apo;
          LCD_data[9] = peri;
        }
      }
      break;

    case DELTAV_MESSAGE:
      if ((LCD_mode == 1) or (LCD_mode == 2)) {
        if (msgSize == sizeof(deltaVMessage)) {
          deltaVMessage mydV;
          mydV = parseMessage<deltaVMessage>(msg);
          String dV = String(mydV.totalDeltaV);
          int stringLength = dV.length();
          dV.remove(stringLength - 3, 3);
          LCD_data[5] = dV;
        }
      }
      break;

    case ALTITUDE_MESSAGE:
      if (LCD_mode == 1) {
        if (msgSize == sizeof(altitudeMessage)) {
          altitudeMessage myAlt;
          myAlt = parseMessage<altitudeMessage>(msg);
          String sealevel = String(myAlt.sealevel);
          String surface = String(myAlt.surface);
          int stringLength = sealevel.length();
          sealevel.remove(stringLength - 3, 3);
          LCD_data[0] = sealevel;
          stringLength = surface.length();
          surface.remove(stringLength - 3, 3);
          LCD_data[1] = surface;
        }
      }
      break;

    case VELOCITY_MESSAGE:
      if (LCD_mode == 1) {
        if (msgSize == sizeof(velocityMessage)) {
          velocityMessage myVel;
          myVel = parseMessage<velocityMessage>(msg);
          String orbital = String(myVel.orbital);
          String surface = String(myVel.surface);
          String vertical = String(myVel.vertical);
          int stringLength = orbital.length();
          orbital.remove(stringLength - 3, 3);
          LCD_data[2] = orbital;
          stringLength = surface.length();
          surface.remove(stringLength - 3, 3);
          LCD_data[3] = surface;
          stringLength = vertical.length();
          vertical.remove(stringLength - 3, 3);
          LCD_data[4] = vertical;
        }
      }
      break;

    case MANEUVER_MESSAGE:
      if (LCD_mode == 2) {
        if (msgSize == sizeof(maneuverMessage)) {
          maneuverMessage myMnv;
          myMnv = parseMessage<maneuverMessage>(msg);
          String deltaVNextManeuver = String(myMnv.deltaVNextManeuver);
          int stringLength = deltaVNextManeuver.length();
          deltaVNextManeuver.remove(stringLength - 3, 3);
          LCD_data[0] = deltaVNextManeuver;
          
          String timeToNextManeuver = String(myMnv.timeToNextManeuver);
          stringLength = timeToNextManeuver.length();
          timeToNextManeuver.remove(stringLength - 3, 3);
          LCD_data[1] = timeToNextManeuver;
          
          String durationNextManeuver = String(myMnv.durationNextManeuver);
          LCD_data[2] = durationNextManeuver;
          
          String deltaVTotal = String(myMnv.deltaVTotal);
          stringLength = deltaVTotal.length();
          deltaVTotal.remove(stringLength - 3, 3);
          LCD_data[3] = deltaVTotal;
        }
      }
      break;

    case ORBIT_MESSAGE:
      if (LCD_mode == 3) {
        if (msgSize == sizeof(orbitInfoMessage)) {
          orbitInfoMessage myOrb;
          myOrb = parseMessage<orbitInfoMessage>(msg);
          String semiMajorAxis = String(myOrb.semiMajorAxis);
          int stringLength = semiMajorAxis.length();
          semiMajorAxis.remove(stringLength - 3, 3);
          LCD_data[0] = semiMajorAxis;
          LCD_data[1] = String(myOrb.eccentricity);
          LCD_data[2] = String(myOrb.inclination);
          LCD_data[3] = String(myOrb.period);
        }
      }
      break;
  }
}
