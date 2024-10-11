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

  #define Stage_                  10
  #define Abort_                  11
  #define Stage_Abort_            12
  #define Camera_                 13
  #define Navigation_             14
  #define Navigation_Time_Ctrl_   15
  #define EA_Groups_Ctrl_         16
  #define EA_Groups_Dspl_         17
  #define EA_Control_Ctrl_        18
  #define EA_Control_Dspl_        19

  #define Time_Ctrl_              20
  #define Time_Dspl_              21
  #define EVA_Ctrl_               22
  #define EVA_Dspl_               23
  #define Ctrl_Sys_Ctrl_          24
  #define Ctrl_Sys_Dspl_          25
  #define Util_Nav_Ctrl_          26
  #define Util_Time_Ctrl_         27
  
  #define Action_Ctrl_            30
  #define Action_Dspl_            31
  #define Action2_Ctrl_           32
  #define Action2_Dspl_           33
  #define Action3_Ctrl_           34
  #define Action3_Dspl_           35
  #define LCD_                    40
  
  #define Analog_Throttle_        45
  #define Rotation_Throttle_      46
  #define Translation_            47
  #define Analog_                 48
  #define Rotation_               49
  #define Throttle_               50
  
  #define Velocity_Ctrl_          60
  #define Velocity_Dspl_          61
  #define Radar_Ctrl_             62
  #define Radar_Dspl_             63
  #define Apsides_Ctrl_           64
  #define Apsides_Dspl_           65
  
  #define System_Ctrl_            70
  #define System_Dspl_            71


//|-------------------|
//|     Registers     |
//|-------------------|

  bool KSP2 = false;
  bool DummyFlag = false;

  byte Action_Ctrl[2] = {};
  int Action_STATE;
  int Action_LAST;
  byte Action_Dspl[2] = {};
  bool AG_Update;

  byte Action2_Ctrl[2] = {};
  int Action2_STATE;
  int Action2_LAST;
  byte Action2_Dspl[2] = {};
  bool AG2_Update;

  byte Action3_Ctrl[2] = {};
  int Action3_STATE;
  int Action3_LAST;
  byte Action3_Dspl[2] = {};
  bool AG3_Update;

  byte currentActionStatus = 0;
  byte Ctrl_Sys_Ctrl[2] = {};
  int ControlSys_combinedBytes;
  int Ctrl_Sys_STATE;
  int Ctrl_Sys_LAST;
  byte Ctrl_Sys_Dspl[1] = {11};
  bool Ctrl_Sys_Update = false;
  bool SAS_pushed;
  bool RCS_pushed;

  byte Navigation[1] = {};
  byte Navigation_STATE;
  byte Navigation_LAST;
  bool MAP_on = false;
  bool NAV_on = false;

  byte Time_Ctrl[1] = {};
  byte Time_STATE;
  byte Time_LAST;
  byte Time_Dspl[1] = {};
  bool F9_press = false;
  bool TW_Update = false;
  int TW_type = TIMEWARP_TO_NEXT_BURN;

  byte Navigation_Time_Ctrl[1] = {};
  byte Navigation_Time_STATE;
  byte Navigation_Time_LAST;

  byte stageB[1] = {};
  byte abortB[1] = {};
  byte Stage_Abort[1] = {};
  byte Stage_Abort_STATE;
  byte Stage_Abort_LAST;

  byte EA_Groups_Ctrl[1] = {};
  int EA_Groups_STATE;
  int EA_Groups_LAST;
  byte EA_Groups_Dspl[1] = {};

  byte Rotation[9] = {};
  int Rotation_STATE;
  int Rotation_LAST;
  bool brakes_pushed;
  bool parking_break;
  byte Translation[9] = {};

  bool isFlying = true;

  byte Camera[2] = {};
  int Camera_combinedBytes;
  int Camera_STATE;
  int Camera_LAST;

  byte EVA_Ctrl[2] = {};
  int EVA_combinedBytes;
  int EVA_STATE;
  int EVA_LAST;
  byte EVA_Dspl[1];
  bool On_EVA = false;
  bool EVA_Update = true;

  byte EA_Control_Ctrl[1] = {};
  int EA_Control_STATE;
  int EA_Control_LAST;
  byte EA_Control_Dspl[1] = {};

  int LCD_transmit = 0;
  byte LCD_mode = 0;
  String LCD_data[10] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};

  byte Throttle[3] = {};

  int Analog_STATE;
  int Analog_LAST;
  byte Analog[8] = {};

  byte Util_Nav_Ctrl[1] = {};
  int Util_Nav_combinedBytes;
  int Util_Nav_STATE;
  int Util_Nav_LAST;

  byte Util_Time_Ctrl[1] = {};
  int Util_Time_combinedBytes;
  int Util_Time_STATE;
  int Util_Time_LAST;


//|-------------------|
//|      Analog       |
//|-------------------|

  rotationMessage myRotation;
  translationMessage myTranslation;
  wheelMessage myWheel;
  rotationMessage myRotationOld;
  translationMessage myTranslationOld;
  wheelMessage myWheelOld;
  #define maxVolt 1023
  #define minVolt 0
  #define plane 0
  #define rocket 1
  #define rover 2

  int Rotation_axis0;
  int Rotation_axis1;
  int Rotation_axis2;
  int Rotation_throttle;
  int Rotation_throttleOld;
  int Rotation_axis0_wheels;
  int Rotation_axis1_wheels;
  int vehicleType;
  int trimp;
  int trimy;
  int trimr;
  bool Trim_On = false;

  int Translation_axis0;
  int Translation_axis1;
  int Translation_axis2;
  int Translation_throttle;
  int Translation_axis0_wheels;
  int Translation_axis1_wheels;
  bool EVA_Button_LAST;
  int cruise_control;
  bool precision = false;
  int prec_divide = 5;
  bool shift_is_down;
  bool ctrl_is_down;
  bool w_is_down;
  bool a_is_down;
  bool s_is_down;
  bool d_is_down;
  bool b_is_down;
  bool f_is_down;
  bool r_is_down;
  bool space_is_down;
  bool EVA_is_down;

  int throttle;
  int throttleOld;
  bool throttle_pcont = false;
  int Analog_axis0;
  int Analog_axis1;
  int Analog_axis2;
  int Analog_axis0_wheels;
  int Analog_axis1_wheels;
  bool brakes_lock = false;
  bool analog_mode = 1;


//|------------------------|
//|      Connections       |
//|------------------------|

  // Connected Modules
  bool Action_Ctrl_Con;
  bool Action2_Ctrl_Con;
  bool Action3_Ctrl_Con;
  bool Ctrl_Sys_Ctrl_Con;
  bool Navigation_Con;
  bool Time_Ctrl_Con;
  bool Stage_Con;
  bool Abort_Con;
  bool Stage_Abort_Con;
  bool Rotation_Throttle_Con;
  bool Rotation_Con;
  bool Translation_Con;
  bool Camera_Con;
  bool EVA_Ctrl_Con;
  bool LCD_Con;
  bool Throttle_Con;
  bool Navigation_Time_Ctrl_Con;
  bool EA_Groups_Ctrl_Con;
  bool Analog_Con;
  bool Analog_Throttle_Con;
  bool EA_Control_Ctrl_Con;
  bool Util_Nav_Ctrl_Con;
  bool Util_Time_Ctrl_Con;
