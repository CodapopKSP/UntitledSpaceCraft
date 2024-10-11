//|-------------------|
//|      Analog       |
//|-------------------|

void readRotation() {
  int raxis1 = (int)Rotation[1] << 8 | (int)Rotation[2];
  int raxis2 = (int)Rotation[3] << 8 | (int)Rotation[4];
  int raxis3 = (int)Rotation[5] << 8 | (int)Rotation[6];
  int rthrottle;
  int throttle_mm;
  if (flip_pitch_axis) {
    Rotation_axis1 = convertAnalog_flipped(raxis2);
  } else {
    Rotation_axis1 = convertAnalog(raxis2);
  }
  if (flip_yaw_axis) {
    Rotation_axis2 = convertAnalog_flipped(raxis3);
  } else {
    Rotation_axis2 = convertAnalog(raxis3);
  }
  if (flip_roll_axis) {
    Rotation_axis0 = convertAnalog_flipped(raxis1);
  } else {
    Rotation_axis0 = convertAnalog(raxis1);
  }

  if (Rotation_Throttle_Con) {
    rthrottle = (int)Rotation[7] << 8 | (int)Rotation[8];
    throttle_mm = minMax_analog(rthrottle);
    // Throttle
    if (!Throttle_Con) {
      if (throttle_mm == minVolt) {
        Rotation_throttle = 0;
      } else if (throttle_mm == maxVolt) {
        Rotation_throttle = maxVolt;
      } else {
        Rotation_throttle = map(throttle_mm, minVolt_, maxVolt_, 3, maxVolt-3);
      }
    }
  }
}

void readTranslation() {
  int taxis1 = (int)Translation[1] << 8 | (int)Translation[2];
  int taxis2 = (int)Translation[3] << 8 | (int)Translation[4];
  int taxis3 = (int)Translation[5] << 8 | (int)Translation[6];
  if (flip_x_axis) {
    Translation_axis0 = convertAnalog_flipped(taxis1);
  } else {
    Translation_axis0 = convertAnalog(taxis1);
  }
  if (flip_y_axis) {
    Translation_axis1 = convertAnalog(taxis2);
  } else {
    Translation_axis1 = convertAnalog_flipped(taxis2);
  }
  if (flip_z_axis) {
    Translation_axis2 = convertAnalog_flipped(taxis3);
  } else {
    Translation_axis2 = convertAnalog(taxis3);
  }
}

void readThrottle() {
  int throttle_read = Throttle[1] << 8 | Throttle[2];
  int throttle_mm = minMax_analog(throttle_read);
  int min_throttle = throttle_min;
  int max_throttle = throttle_max;
  int max_send_throttle = INT16_MAX;

  if (throttle_mm < min_throttle) {
    throttle = 0;
  } else if (throttle_mm > max_throttle) {
    throttle = max_send_throttle;
  } else {
    throttle = map(throttle_mm, min_throttle, max_throttle, 0, max_send_throttle);
  }
}

void readAnalog() {
  int raxis1 = (int)Analog[1] << 8 | (int)Analog[2];
  int raxis2 = (int)Analog[3] << 8 | (int)Analog[4];
  int raxis3 = (int)Analog[5] << 8 | (int)Analog[6];

  Analog_axis1 = convertAnalog(raxis2);
  Analog_axis0 = convertAnalog(raxis1);
  Analog_axis2 = convertAnalog(raxis3);

  // Throttle
  if (Analog_Throttle_Con) {
    int rthrottle = (int)Analog[7] << 8 | (int)Analog[8];
    int throttle_mm = minMax_analog(rthrottle);

    if (throttle_mm == minVolt) {
      Rotation_throttle = 0;
    } else if (throttle_mm == maxVolt) {
      Rotation_throttle = INT16_MAX;
    } else {
      Rotation_throttle = map(throttle_mm, minVolt_, maxVolt_, 32, INT16_MAX-32);
    } 
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
    return map(read0, deadZone_max, maxVolt, joystick_center, minVolt);
  } else if (read0 < deadZone_min) {
    return map(read0, minVolt, deadZone_min, maxVolt, joystick_center);
  } else {
    return joystick_center;
  }
}

int convertAnalog_flipped(int read0) {
  if (read0 > deadZone_max) {
    return map(read0, deadZone_max, maxVolt, joystick_center, maxVolt);
  } else if (read0 < deadZone_min) {
    return map(read0, minVolt, deadZone_min, minVolt, joystick_center);
  } else {
    return joystick_center;
  }
}
