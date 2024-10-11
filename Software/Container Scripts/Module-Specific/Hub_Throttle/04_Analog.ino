//|-------------------|
//|      Analog       |
//|-------------------|

void analogSetup() {
}

void readAnalogs() {
  int throttle_read = Throttle[1] << 8 | Throttle[2];
  int throttle_mm = minMax_analog(throttle_read);
  int min_throttle = throttle_min;
  int max_throttle = throttle_max;
  int max_send_throttle = INT16_MAX;

  if (throttle_pcont) {
    min_throttle = throttle_pmin;
    max_throttle = throttle_pmax;
    max_send_throttle = 5000;
  }
  if (throttle_mm < min_throttle) {
    throttle = 0;
  } else if (throttle_mm > max_throttle) {
    throttle = max_send_throttle;
  } else {
    throttle = map(throttle_mm, min_throttle, max_throttle, 0, max_send_throttle);
  }
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
