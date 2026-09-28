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
  
  #define Fuel_Ctrl_       50
  #define Fuel_Dspl_       51


//|-------------------|
//|     Registers     |
//|-------------------|


  // Connected Modules
  bool Fuel_Ctrl_Con;

//|----------------------|
//|      Resources       |
//|----------------------|

/* 3 6 7
  int fuel_resources[6] = {0,0,0,0,0,0};
  int fuel_resources_stage[6] = {0,0,0,0,0,0};*/

  byte fuel1 = 0;
  byte fuel2 = 0;
  byte fuel3 = 0;
  byte fuel4 = 0;
  byte fuel5 = 0;
  byte fuel6 = 0;

  byte sfuel1 = 0;
  byte sfuel2 = 0;
  byte sfuel3 = 0;
  byte sfuel4 = 0;
  byte sfuel5 = 0;
  byte sfuel6 = 0;

  int test = 3;
