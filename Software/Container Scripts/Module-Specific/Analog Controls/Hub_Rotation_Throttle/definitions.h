//|-------------------|
//|   Hub Connector   |
//|-------------------|

  #define Analog_5  A7
  #define Analog_4  A6
  #define Analog_3  A3
  #define Analog_2  A2
  #define Analog_1  A1
  #define Analog_0  A0
  #define Digital_1 3
  #define Digital_0 2
  
  #define SDA_      A4
  #define SCL_      A5
  #define Reset     7
  #define Digital_4 6
  #define Digital_3 5
  #define Digital_2 4


//|-------------------|
//|     Addresses     |
//|-------------------|

  #define Stage_           10
  #define Abort_           11
  #define Stage_Abort_     12
  #define Camera_          13
  #define Navigation_      14

  #define Time_Ctrl_       20
  #define Time_Dspl_       21
  #define EVA_Ctrl_        22
  #define EVA_Dspl_        23
  #define Ctrl_Sys_Ctrl_   24
  #define Ctrl_Sys_Dspl_   25
  
  #define Action_Ctrl_     30
  #define Action_Dspl_     31
  #define Action2_Ctrl_    32
  #define Action2_Dspl_    33
  #define Action3_Ctrl_    34
  #define Action3_Dspl_    35
  #define Analog_          45
  #define Rotation_        46
  
  #define Fuel_Ctrl_       50
  #define Fuel_Dspl_       51
  
  #define Velocity_Ctrl_   60
  #define Velocity_Dspl_   61
  #define Radar_Ctrl_      62
  #define Radar_Dspl_      63
  #define Apsides_Ctrl_    64
  #define Apsides_Dspl_    65
  
  #define System_Ctrl_     70
  #define System_Dspl_     71


//|-------------------|
//|     Registers     |
//|-------------------|

  byte Rotation[9] = {};

  // Connected Modules
  bool Rotation_Con;


//|-------------------|
//|      Analog       |
//|-------------------|

  rotationMessage myRotation;
  wheelMessage myWheel;
  #define maxVolt 1023
  #define minVolt 0
  #define maxVolt_ 1020
  #define minVolt_ 3
  #define deadZone_min 466
  #define deadZone_max 557

  #define plane 0
  #define rocket 1
  #define rover 2

  int Rotation_axis0;
  int Rotation_axis1;
  int Rotation_axis2;
  int Rotation_throttle;
  int Rotation_axis0_wheels;
  int Rotation_axis1_wheels;

  int vehicleType;
  int trimp;
  int trimy;
  int trimr;
  
