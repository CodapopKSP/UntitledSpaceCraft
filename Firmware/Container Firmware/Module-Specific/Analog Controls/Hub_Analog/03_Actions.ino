//|-------------------|
//|      Actions      |
//|-------------------|

void Analog_Action() {
  if (Analog[0] != Analog_LAST) {
    lastDebounceTime_b = millis();
  }
  if (Analog[0] != Analog_STATE) {
    Analog_STATE = Analog[0];
    if (Analog[0] & 4){
      if (Analog[0] & 1) {
        brakes_lock = true;
      } else {
        brakes_lock = false;
      }
      if (!(currentActionStatus & BRAKES_ACTION)) {
        mySimpit.activateAction(BRAKES_ACTION);
      }
    }
    if (!(Analog[0] & 4) && (currentActionStatus & BRAKES_ACTION) && !(brakes_lock)){
      mySimpit.deactivateAction(BRAKES_ACTION);
    }
  }
  Analog_LAST = Analog_STATE;

  if((Analog[0] & 64) && !(currentActionStatus & GEAR_ACTION)){
    mySimpit.activateAction(GEAR_ACTION);
  }
  if(!(Analog[0] & 64) && (currentActionStatus & GEAR_ACTION)){
    mySimpit.deactivateAction(GEAR_ACTION);
  }

  if(Analog[0] & 32){
    analog_mode = 1;
  } else {
    analog_mode = 0;
  }

  if (Analog[0] & 8) {
    vehicleType = rover;
  } else if (Analog[0] & 16) {
    vehicleType = plane;
  } else {
    vehicleType = rocket;
  }

  // Reset Trim
  if (Analog[0] & 2) {
    trimy = 0;
    trimp = 0;
    trimr = 0;
    cruise_control = 0;
    myWheel.throttle = 0;
  }

  // Rotation 
  if (analog_mode == 1) {
    // Plane
    if (vehicleType == 0) {
      myRotation.yaw = Analog_axis2;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis0;
      myWheel.throttle = Analog_axis1_wheels;
      myWheel.steer = Analog_axis0_wheels;
  
      // Trim
      if (Analog[0] & 1) {
        trimy = Analog_axis2;
        trimp = Analog_axis1;
        trimr = Analog_axis0;
      }
  
      myRotation.yaw = checkTrim(trimy, Analog_axis2);
      myRotation.pitch = checkTrim(trimp, Analog_axis1);
      myRotation.roll = checkTrim(trimr, Analog_axis0);
    }
    
    // Rocket
    if (vehicleType == 1) {
      myRotation.yaw = Analog_axis0;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis2;
      myWheel.throttle = 0;
      myWheel.steer = 0;
    }
    
    // Rover
    if (vehicleType == 2) {
      myRotation.yaw = Analog_axis2;
      myRotation.pitch = Analog_axis1;
      myRotation.roll = Analog_axis0;
    }
    myTranslation.X = 0;
    myTranslation.Y = 0;
    myTranslation.Z = 0;
    
  // Translation
  }
  if (analog_mode == 0) {
    
    myTranslation.X = Analog_axis0;
    myTranslation.Y = Analog_axis1;
    myTranslation.Z = Analog_axis2;
    myRotation.yaw = 0;
    myRotation.pitch = 0;
    myRotation.roll = 0;
    
    // Rover
    if (vehicleType == 2) {
      // Cruise
      if (Analog[0] & 1) {
        cruise_control = Analog_axis1_wheels;
      }
      if ((cruise_control != 0) and (Analog_axis1_wheels <= cruise_control)) {
        myWheel.throttle = cruise_control;
      } else {
        myWheel.throttle = Analog_axis1_wheels;
      }
      myWheel.steer = Analog_axis0_wheels;
    }
  }
  // Execute
  mySimpit.send(ROTATION_MESSAGE, myRotation);
  mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
  mySimpit.send(WHEEL_MESSAGE, myWheel);
}
