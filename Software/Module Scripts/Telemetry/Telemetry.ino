#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <Wire.h>

String ap = "0";
String apTime = "0";
String pe = "0";
String peTime = "0";

String input0 = "0";
String input1 = "0";
String input2 = "0";
String input3 = "0";
String input4 = "0";
String input5 = "0";

#define own_address 40
#define alt_vel_button 9
#define mnvr_button 8
#define orbit_button 7
#define fuel_button 6

byte mode = 4;

// End of constructor list
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, /* clock=*/ 11 /* A4 */ , /* data=*/ 13 /* A2 */, /* CS=*/ 10 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  pinMode(alt_vel_button, INPUT);
  pinMode(mnvr_button, INPUT);
  pinMode(orbit_button, INPUT);
  pinMode(fuel_button, INPUT);
  u8g2.begin();
  Wire.begin(own_address);
  Wire.onReceive(onI2CReceive);
  Wire.onRequest(onI2CRequest);
  Serial.begin(9600);
}

void loop(void) {
  u8g2.firstPage();
  do {
    if (input0 == "X") {
      mode = 4;
    }
    if (digitalRead(alt_vel_button)) {
      mode = 1;
    }
    if (digitalRead(mnvr_button)) {
      mode = 2;
    }
    if (digitalRead(orbit_button)) {
      mode = 3;
    }
    if (digitalRead(fuel_button)) {
      mode = 0;
    }
    u8g2.setFont(u8g2_font_6x10_tf);
    if (mode == 0) {
      displayFuel(input0, input1, input2, input3, input4, input5);
    }
    else if (mode == 1) {
      drawApsides(ap, apTime, pe, peTime);
      displayTelemetry(input0, input1, input2, input3, input4, input5);
    }
    else if (mode == 2) {
      drawApsides(ap, apTime, pe, peTime);
      displayMnvrInfo(input0, input1, input2, input3, input5);
    }
    else if (mode == 3) {
      drawApsides(ap, apTime, pe, peTime);
      displayOrbitInfo(input0, input1, input2, input3);
    }
    else if (mode == 4) {
      u8g2.clearDisplay();
    }
  } while ( u8g2.nextPage() );
}

void onI2CRequest() {
  Wire.write(mode);
}

void onI2CReceive(int byteCount) {
  int messType = Wire.read();
  if (messType == 0) {
    readWireData(input0);
    readWireData(input1);
    readWireData(input2);
  } else if (messType == 1) {
    readWireData(input3);
    readWireData(input4);
    readWireData(input5);
  } else {
    readWireData(ap);
    readWireData(pe);
    readWireData(apTime);
    readWireData(peTime);
  }
}

void readWireData(String& input) {
  int packetSize = Wire.read();
  char packets[packetSize+1];
  for (int i = 0; i < packetSize; i++) {
    packets[i] = Wire.read();
  }
  packets[packetSize] = '\0';
  input = packets;
}

void displayOrbitInfo(String sma, String eccent, String inclin, String period) {
  drawOrbitLines();
  drawInfo("SMA", 11, getUnits(sma));
  drawInfo("ECCNT", 27, eccent);
  drawInfo("INCLN", 43, inclin);
  drawInfo("PERIOD", 59, formatSeconds(period));
}

void drawOrbitLines() {
  u8g2.drawHLine(82, 31, 44);
  u8g2.drawVLine(82, 0, 64);
  u8g2.drawVLine(36, 0, 64);
  u8g2.drawHLine(36, 15, 46);
  u8g2.drawHLine(36, 31, 46);
  u8g2.drawHLine(36, 47, 46);
}


void displayMnvrInfo(String dV, String timeToM, String burnTime, String totalMdV, String shipdV) {
  drawMnvrLines();
  drawMnvrNodeInfo(41, 8, "NEXT MNVR");
  drawMnvrNodeInfo(41, 18, getUnits(dV));
  drawMnvrNodeInfo(41, 28, formatSeconds(timeToM));
  drawMnvrNodeInfo(41, 38, burnTime + "s");
  drawInfo("ALL MV", 52, getUnits(totalMdV));
  drawInfo("dV", 63, getUnits(shipdV));
}

void drawMnvrNodeInfo(int x, int y, String value) {
  int width;
  width = u8g2.getStrWidth(value.c_str());
  u8g2.drawStr(x-width/2, y, value.c_str());
}

void drawMnvrLines() {
  u8g2.drawHLine(82, 31, 44);
  u8g2.drawVLine(82, 0, 64);
  u8g2.drawVLine(36, 42, 22);
  u8g2.drawHLine(0, 42, 82);
  u8g2.drawHLine(36, 53, 46);
}

void displayTelemetry(String altSea, String altSurf, String velOrb, String velSurf, String velVert, String shipdV) {
  drawTelemLines();
  drawInfo("A-SEA", 8, getUnits(altSea));
  drawInfo("A-SRF", 19, getUnits(altSurf));
  drawInfo("V-OBT", 30, getUnits(velOrb));
  drawInfo("V-SRF", 41, getUnits(velSurf));
  drawInfo("V-VRT", 52, getUnits(velVert));
  drawInfo("dV", 63, getUnits(shipdV));
}

void drawTelemLines() {
  u8g2.drawHLine(82, 31, 44);
  u8g2.drawVLine(82, 0, 64);
  u8g2.drawVLine(36, 0, 64);
  u8g2.drawHLine(36, 9, 46);
  u8g2.drawHLine(36, 20, 46);
  u8g2.drawHLine(36, 31, 46);
  u8g2.drawHLine(36, 42, 46);
  u8g2.drawHLine(36, 53, 46);
}

void drawInfo(String iName, int vPos, String value) {
  int width;
  width = u8g2.getStrWidth(iName.c_str());
  u8g2.drawStr(17-width/2, vPos, iName.c_str());
  width = u8g2.getStrWidth(value.c_str());
  u8g2.drawStr(80-width, vPos, value.c_str());
}

void drawApsides(String ap_, String apTime_, String pe_, String peTime_) {
  u8g2.drawStr(100, 9, "AP");
  ap_ = getUnits(ap_);
  apTime_ = formatSeconds(apTime_);
  int width = u8g2.getStrWidth(ap_.c_str());
  u8g2.drawStr(126-(width), 19, ap_.c_str());
  width = u8g2.getStrWidth(apTime_.c_str());
  u8g2.drawStr(126-(width), 29, apTime_.c_str());
  
  u8g2.drawStr(100, 41, "PE");
  pe_ = getUnits(pe_);
  peTime_ = formatSeconds(peTime_);
  width = u8g2.getStrWidth(pe_.c_str());
  u8g2.drawStr(126-(width), 51, pe_.c_str());
  width = u8g2.getStrWidth(peTime_.c_str());
  u8g2.drawStr(126-(width), 61, peTime_.c_str());
}

String formatSeconds(String secondsChar) {
  unsigned long seconds = strtoul(secondsChar.c_str(), NULL, 10);
  if (seconds >= 21600) {
    int days = seconds / 21600;
    return String(days) + "d";
  }
  int hours = seconds / 3600;
  int minutes = (seconds % 3600) / 60;
  seconds = seconds % 60;
  String minutesStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);
  String secondsStr = (seconds < 10) ? "0" + String(seconds) : String(seconds);
  return String(hours) + ":" + minutesStr + ":" + secondsStr;
}

String getUnits(String value) {
  int stringLength = value.length();
  if (stringLength > 13) {
    value.remove(stringLength - 12, 12);
    value += " Tm";
  }
  if (stringLength > 10) {
    value.remove(stringLength - 9, 9);
    value += " Gm";
  }
  else if (stringLength > 7) {
    value.remove(stringLength - 6, 6);
    value += " Mm";
  }
  else if (stringLength > 4) {
    value.remove(stringLength - 3, 3);
    value += " km";
  }
  else {
    value = value + " m";
  }
  return value;
}

void displayFuel(String LF, String OX, String SF, String EC, String XE, String MP) {
  u8g2.drawHLine(2, 54, 124);
  drawFuelGauge(16, "LF", LF.toInt());
  drawFuelGauge(37, "OX", OX.toInt());
  drawFuelGauge(58, "SF", SF.toInt());
  drawFuelGauge(79, "EC", EC.toInt());
  drawFuelGauge(100, "XE", XE.toInt());
  drawFuelGauge(121, "MP", MP.toInt());
  u8g2.drawVLine(21, 0, 64);
  u8g2.drawVLine(42, 0, 64);
  u8g2.drawVLine(63, 0, 64);
  u8g2.drawVLine(84, 0, 64);
  u8g2.drawVLine(105, 0, 64);
}

void drawFuelGauge(int vert, String fuelName, int fuel) {
  drawFuelBox(vert-10, fuel);
  u8g2.drawStr(vert-10, 64, fuelName.c_str());
  u8g2.drawHLine(vert, 0, 2);
  u8g2.drawHLine(vert, 12, 2);
  u8g2.drawHLine(vert, 25, 2);
  u8g2.drawHLine(vert, 37, 2);
  u8g2.drawHLine(vert, 51, 2);
}

void drawFuelBox(int pos, int fuel) {
  int difference = 52 - fuel;
  u8g2.drawBox(pos, difference, 10, fuel);
}
