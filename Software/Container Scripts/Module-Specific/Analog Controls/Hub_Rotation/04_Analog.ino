//|-------------------|
//|      Analog       |
//|-------------------|

void analogSetup() {
  myRotation.mask = 7;
  myWheel.mask = 7;
  //analogReference(EXTERNAL);
}

void readAnalogs() {
  int raxis1 = (int)Rotation[1] << 8 | (int)Rotation[2];
  int raxis2 = (int)Rotation[3] << 8 | (int)Rotation[4];
  int raxis3 = (int)Rotation[5] << 8 | (int)Rotation[6];
  Rotation_axis0 = convertAnalog(raxis1);
  Rotation_axis1 = convertAnalog(raxis2);
  Rotation_axis2 = convertAnalog(raxis3);
  Rotation_axis0_wheels = convertAnalog_flipped(raxis1);
  Rotation_axis1_wheels = convertAnalog_flipped(raxis2);
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
