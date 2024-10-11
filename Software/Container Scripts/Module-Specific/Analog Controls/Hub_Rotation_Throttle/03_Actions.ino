//|-------------------|
//|      Actions      |
//|-------------------|

void Rotation_Action() {
  if (Rotation[0] & 2) {
    vehicleType = rover;
  } else if (Rotation[0] & 4) {
    vehicleType = plane;
  } else {
    vehicleType = rocket;
  }

  // Reset Trim
  if (Rotation[0] & 8) {
    trimy = 0;
    trimp = 0;
    trimr = 0;
  }

  // Plane
  if (vehicleType == 0) {
    myRotation.yaw = Rotation_axis2;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis0;
    myWheel.throttle = Rotation_axis1_wheels;
    myWheel.steer = Rotation_axis0_wheels;

    // Trim
    if (Rotation[0] & 1) {
      trimy = Rotation_axis2;
      trimp = Rotation_axis1;
      trimr = Rotation_axis0;
    }

    myRotation.yaw = checkTrim(trimy, Rotation_axis2);
    myRotation.pitch = checkTrim(trimp, Rotation_axis1);
    myRotation.roll = checkTrim(trimr, Rotation_axis0);
  }
  
  // Rocket
  if (vehicleType == 1) {
    myRotation.yaw = Rotation_axis0;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis2;
    myWheel.throttle = 0;
    myWheel.steer = 0;
  }
  
  // Rover
  if (vehicleType == 2) {
    myRotation.yaw = Rotation_axis2;
    myRotation.pitch = Rotation_axis1;
    myRotation.roll = Rotation_axis0;
    myWheel.throttle = Rotation_axis1_wheels;
    myWheel.steer = Rotation_axis0_wheels;
  }

  // Execute
  mySimpit.send(ROTATION_MESSAGE, myRotation);
  mySimpit.send(THROTTLE_MESSAGE, Rotation_throttle);
  mySimpit.send(WHEEL_MESSAGE, myWheel);
}
