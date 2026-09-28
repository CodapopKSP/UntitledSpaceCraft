//|-------------------|
//|      Actions      |
//|-------------------|

void Translation_Action() {

  // Precision Control
  if (Translation[0] & 2) {
    precision = true;
  } else {
    precision = false;
  }

  // Parking Break On
  if ((Translation[0] & 4) and !parking_break){
    mySimpit.activateAction(BRAKES_ACTION);
    parking_break = true;
    cruise_control = 0;
  }

  // Parking Break Off
  if(!(Translation[0] & 4) && !brakes_pushed && parking_break){
    mySimpit.deactivateAction(BRAKES_ACTION);
    parking_break = false;
  }

  // Brakes
  if((Translation[0] & 8) && !brakes_pushed && !parking_break){
    mySimpit.activateAction(BRAKES_ACTION);
    cruise_control = 0;
    brakes_pushed = true;
  }
  if(!(Translation[0] & 8) && brakes_pushed){
    brakes_pushed = false;
    if (!parking_break) {
      mySimpit.deactivateAction(BRAKES_ACTION);
    }
  }

  // Reset Cruise
  if (Translation[0] & 16) {
    cruise_control = 0;
  }

  if (precision) {
    myTranslation.X = Translation_axis0/10;
    myTranslation.Y = Translation_axis1/10; // Maybe flip this axis
    myTranslation.Z = Translation_axis2/10;
  } else {
    myTranslation.X = Translation_axis0;
    myTranslation.Y = Translation_axis1; // Maybe flip this axis
    myTranslation.Z = Translation_axis2;
  }

  // Set Cruise Control and Wheel Throttle/Steering
  if (Translation[0] & 1) {
    cruise_control = Translation_axis1_wheels;
  }
  if ((cruise_control != 0) and (Translation_axis1_wheels <= cruise_control)) {
    myWheel.throttle = cruise_control;
  } else {
    myWheel.throttle = Translation_axis1_wheels;
  }
  myWheel.steer = Translation_axis0_wheels;

  // Execute
  mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
  mySimpit.send(WHEEL_MESSAGE, myWheel);
}
