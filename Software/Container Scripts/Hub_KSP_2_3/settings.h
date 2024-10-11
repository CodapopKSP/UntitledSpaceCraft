//|----------------------|
//|   General Settings   |
//|----------------------|

  // This value determines how often the controller will update, in milliseconds.
  // If your controller frequently loses connection, you can try increasing this value.
  // Default value is 10.
  // You may try something on the scale of 20 - 100.

  #define update_time 10


//|------------------------------|
//|   Throttle Module Settings   |
//|------------------------------|

  // These values correspond with the numbers written on the bottom of the
  // Throttle module. The numbers on the bottom are the calibration for
  // the throttle control.
  // By default the deadzone value is 5 away from what was measured on the test bench.
  // Min values are 0.
  // Max values are 1023.
  
  // If your throttle lever has too much of a deadzone at the top or bottom,
  // you may lower the min values or raise the max values.
  // Alternatively, if your throttle lever isn't quite reaching zero or max,
  // you may raise the min values or lower the max values.

  #define throttle_min 280
  #define throttle_max 894
  #define throttle_pmin 250
  #define throttle_pmax 800


//|---------------------|
//|   Analog Settings   |
//|---------------------|

  // These values handle the deadzones for all joystick modules as well as 
  // the throttle knob on some analog modules.
  // Min values are 0.
  // Max values are 1023.
  
  // If your analog sticks have a deadzone in the center that is too large,
  // you may raise deadZone_min and/or lower deadZone_max.
  // If your analog sticks have a deadzone in the center that is too small,
  // (such as the stick giving input when you aren't touching it) you may
  // lower deadZone_min and/or raise deadZone_max.

  // If the throttle knob has deadzones that are too large, you may lower
  // minVolt_ and/or raise maxVolt_.
  // If the throttle knob has deadzones that are too small, (such as the
  // throttle giving input when it is off, or never reaching 100%), you may
  // raise minVolt_ and/or lower maxVolt_.
  
  #define deadZone_min 466
  #define deadZone_max 557
  #define maxVolt_ 1020
  #define minVolt_ 3


//|-----------------------|
//|   Timewarp Settings   |
//|-----------------------|

  // This value is the number of seconds before the start of a burn that
  // the 'TO MNVR' button will warp to.
  // Default value is -90.0f;, meaning 90 seconds before the burn.
  // If, for instance, you want 10 seconds before, you would use -10.0f;.
  
  float TW_delay = -90.0f;







  
