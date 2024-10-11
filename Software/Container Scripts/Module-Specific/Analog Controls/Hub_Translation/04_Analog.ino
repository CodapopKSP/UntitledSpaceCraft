//|-------------------|
//|      Analog       |
//|-------------------|

void analogSetup() {
  myTranslation.mask = 7;
  myWheel.mask = 7;
  //analogReference(EXTERNAL);
}

void readAnalogs() {
  int taxis1 = (int)Translation[1] << 8 | (int)Translation[2];
  int taxis2 = (int)Translation[3] << 8 | (int)Translation[4];
  int taxis3 = (int)Translation[5] << 8 | (int)Translation[6];
  Translation_axis0 = convertAnalog(taxis1);
  Translation_axis1 = convertAnalog(taxis2);
  Translation_axis2 = convertAnalog(taxis3);
  Translation_axis0_wheels = convertAnalog_flipped(taxis1);
  Translation_axis1_wheels = convertAnalog_flipped(taxis2);
}

int minMax_analog(int input) {
  if (input > maxVolt_) {
    return maxVolt;
  }
  if (input < minVolt_) {
    return minVolt;
  }
  return input;
}

int convertAnalog(int read0) {
  if (read0 > deadZone_max) {
    return map(read0, deadZone_max, maxVolt, 0, INT16_MIN);
  } else if (read0 < deadZone_min) {
    return map(read0, minVolt, deadZone_min, INT16_MAX, 0);
  } else {
    return 0;
  }
}

int convertAnalog_flipped(int read0) {
  if (read0 > deadZone_max) {
    return map(read0, deadZone_max, maxVolt, 0, INT16_MAX);
  } else if (read0 < deadZone_min) {
    return map(read0, minVolt, deadZone_min, INT16_MIN, 0);
  } else {
    return 0;
  }
}

int checkTrim(int trim_register, int analog_input) {
  int output_clean;
  long output = long(trim_register) + long(analog_input);
  if (output > INT16_MAX) {
    output_clean = INT16_MAX;
  }
  else if (output < INT16_MIN) {
    output_clean = INT16_MIN;
  }
  else {
    output_clean = output;
  }
  return output_clean;
}
