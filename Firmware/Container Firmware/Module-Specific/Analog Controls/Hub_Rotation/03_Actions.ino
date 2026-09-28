//|-------------------|
//|      Actions      |
//|-------------------|

void Rotation_Action() {
  if (Rotation[0] != Rotation_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Rotation[0] != Rotation_STATE) {
    Rotation_STATE = Rotation[0];
    if ((Rotation[0] & 1) && !(currentActionStatus & LIGHT_ACTION)){
      mySimpit.activateAction(LIGHT_ACTION);
    }
    if ((Rotation[0] & 1) && (currentActionStatus & LIGHT_ACTION)){
      mySimpit.deactivateAction(LIGHT_ACTION);
    }
  }
  Rotation_LAST = Rotation_STATE;

  if((Rotation[0] & 32) && !(currentActionStatus & GEAR_ACTION)){
    mySimpit.activateAction(GEAR_ACTION);
  }
  if(!(Rotation[0] & 32) && (currentActionStatus & GEAR_ACTION)){
    mySimpit.deactivateAction(GEAR_ACTION);
  }

  if (Rotation[0] & 8) {
    vehicleType = rover;
  } else if (Rotation[0] & 16) {
    vehicleType = plane;
  } else {
    vehicleType = rocket;
  }

  // Reset Trim
  if (Rotation[0] & 2) {
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
    if (Rotation[0] & 4) {
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
  }

  if (precision) {
    myRotation.yaw = myRotation.yaw/prec_divide;
    myRotation.pitch = myRotation.pitch/prec_divide;
    myRotation.roll = myRotation.roll/prec_divide;
  }

  // Execute
  mySimpit.send(ROTATION_MESSAGE, myRotation);
  mySimpit.send(WHEEL_MESSAGE, myWheel);
}
