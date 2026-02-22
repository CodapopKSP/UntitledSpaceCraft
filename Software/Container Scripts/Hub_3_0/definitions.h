//|----------------------|
//|     Game and OS      |
//|----------------------|

/*
  This determines the OS of the host computer and game profile.
  The OS mostly affects modifier keys and the game profile affects the
  keybindings of the controller.
*/

#define WINDOWS 1
#define LINUX   2
bool KSP2 = false;
bool keyboardEmulation = false;

#if OPERATING_SYSTEM == WINDOWS
  #define KSP_MOD_KEY  KEY_LEFT_SHIFT
  #define KSP_MOD_KEY2 KEY_LEFT_ALT
#elif OPERATING_SYSTEM == LINUX
  #define KSP_MOD_KEY  KEY_LEFT_SHIFT
  #define KSP_MOD_KEY2 KEY_RIGHT_SHIFT
#endif


//|-------------------|
//|     I/O Pins      |
//|-------------------|

/*
  This determines the physical I/O pins of the controller.
  These should not ever be changed unless you are very significantly
  modifying the hardware of the controller.
*/

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

/*
  This determines the addresses which are used to identify the modules.
  If you expand the system with custom modules, you can add more addresses here.
*/

  #define Stage_                  10
  #define Abort_                  11
  #define Executive_Actions_      12
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

/*
  This determines the registers which are used to store the state of the buttons and potentiometers.
*/

  byte Action_Ctrl[2] = {};
  byte Action2_Ctrl[2] = {};
  byte Action3_Ctrl[2] = {};
  byte Ctrl_Sys_Ctrl[2] = {};
  byte Navigation[1] = {};
  byte Time_Ctrl[1] = {};
  byte Navigation_Time_Ctrl[1] = {};
  byte Stage_Button[1] = {};
  byte Abort_Button[1] = {};
  byte Executive_Actions[1] = {};
  byte EA_Groups_Ctrl[1] = {};
  byte Camera[2] = {};
  byte Rotation[9] = {};
  byte Translation[9] = {};
  byte EVA_Ctrl[2] = {};
  byte EA_Control_Ctrl[1] = {};
  byte Throttle[3] = {};
  byte Util_Nav_Ctrl[1] = {};
  byte Util_Time_Ctrl[1] = {};
  byte Analog[8] = {};

  byte Action_Dspl[2] = {};
  byte Action2_Dspl[2] = {};
  byte Action3_Dspl[2] = {};
  byte Ctrl_Sys_Dspl[1] = {11};
  byte Time_Dspl[1] = {};
  byte EA_Groups_Dspl[1] = {};
  byte EVA_Dspl[1];
  byte EA_Control_Dspl[1] = {};

  int Action_STATE;
  int Action2_STATE;
  int Action3_STATE;
  int Ctrl_Sys_STATE;
  byte Navigation_STATE;
  byte Time_STATE;
  byte Navigation_Time_STATE;
  byte Executive_Actions_STATE;
  byte Stage_STATE;
  byte Abort_STATE;
  byte EA_Groups_STATE;
  int Rotation_STATE;
  int Translation_STATE;
  int Camera_STATE;
  int EVA_STATE;
  byte EA_Control_STATE;
  byte Throttle_STATE;
  int Analog_STATE;
  byte Util_Nav_STATE;
  byte Util_Time_STATE;

  int Action_LAST;
  int Action2_LAST;
  int Action3_LAST;
  int Ctrl_Sys_LAST;
  byte Navigation_LAST;
  byte Time_LAST;
  byte Navigation_Time_LAST;
  byte Executive_Actions_LAST;
  byte Stage_LAST;
  byte Abort_LAST;
  byte EA_Groups_LAST;
  int Rotation_LAST;
  int Translation_LAST;
  int Camera_LAST;
  int EVA_LAST;
  byte EA_Control_LAST;
  byte Throttle_LAST;
  int Analog_LAST;
  byte Util_Nav_LAST;
  byte Util_Time_LAST;

//|-----------------------|
//|     Miscellaneous     |
//|-----------------------|

/*
  This determines the miscellaneous variables which are used to store the state of the controller.
*/

  byte currentActionStatus = 0;
  int Nav_KSP1_KSP2 = '`';
  int TW_type = TIMEWARP_TO_NEXT_BURN;
  bool brakes_pushed;
  bool parking_break;
  bool isFlying = true;
  bool On_EVA = false;
  int LCD_transmit = 0;
  byte LCD_mode = 0;
  String LCD_data[10] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};

  int ControlSys_combinedBytes;
  int Camera_combinedBytes;
  int EVA_combinedBytes;
  int Util_Nav_combinedBytes;
  int Util_Time_combinedBytes;

  #define NO_DISPLAY 0
  #define ONE_BYTE 1
  #define TWO_BYTES 2


//|------------------------|
//|     Keypress Flags     |
//|------------------------|

/*
  These are keypress flags that determine if a button is currently pressed.
*/

  bool Stage_flag = false;
  bool Abort_flag = false;
  bool Executive_Actions_flag[2] = {false, false};
  bool EA_Groups_flag[7] = {false, false, false, false, false, false, false};
  bool EA_Control_flag[7] = {false, false, false, false, false, false, false};
  bool Time_flag[8] = {false, false, false, false, false, false, false};
  bool Navigation_flag[8] = {false, false, false, false, false, false, false, false};
  bool Navigation_Map_flag = false;
  bool Navigation_NAV_flag = false;
  bool Navigation_Time_flag[8] = {false, false, false, false, false, false, false, false};
  bool Util_Nav_flag[8] = {false, false, false, false, false, false, false, false};
  bool Util_Time_flag[8] = {false, false, false, false, false, false, false, false};
  bool EVA_flag[11] = {false, false, false, false, false, false, false, false, false, false, false};
  bool Camera_flag[10] = {false, false, false, false, false, false, false, false, false, false};
  bool Analog_flag[13] = {false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool Rotation_flag[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
  bool Translation_flag[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
  bool Throttle_flag[3] = {false, false, false};
  bool Ctrl_Systems_flag[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
  bool Action_flag[10] = {false, false, false, false, false, false, false, false, false, false};
  bool Action2_flag[10] = {false, false, false, false, false, false, false, false, false, false};
  bool Action3_flag[10] = {false, false, false, false, false, false, false, false, false, false};


//|-------------------|
//|      Analog       |
//|-------------------|

/*
  These values are used by the analog controls system.
*/

  enum Analog_Message_Type {
    ANALOG_ROTATION_MESSAGE,
    ANALOG_TRANSLATION_MESSAGE,
    ANALOG_WHEEL_MESSAGE,
    ANALOG_THROTTLE_MESSAGE,
  };

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

/*
  These are connection flags that determine if a module is currently connected.
  They are set to false by default and are set to true when a module is connected.
*/

  bool Action_Ctrl_Con;
  bool Action2_Ctrl_Con;
  bool Action3_Ctrl_Con;
  bool Ctrl_Sys_Ctrl_Con;
  bool Navigation_Con;
  bool Time_Ctrl_Con;
  bool Stage_Con;
  bool Abort_Con;
  bool Executive_Actions_Con;
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


//|------------------------------|
//|      Emulation Helpers       |
//|------------------------------|

/*
  These are variables that assist the controller in organizing keyboard emulation
  keybindings. They are ordered lists of keys that a module might use to perform an action.
*/
