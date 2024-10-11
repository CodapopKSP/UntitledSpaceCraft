//|----------------------|
//|   General Settings   |
//|----------------------|
  /*
    This value determines how often the controller will update, in milliseconds.
    If your controller frequently loses connection, you can try increasing this value.
    Default value is 10.
    You may try something on the scale of 20 - 100.
  */
  
  #define update_time 10


//|------------------------------|
//|   Throttle Module Settings   |
//|------------------------------|
  /*
    These values correspond with the numbers written on the bottom of the
    Throttle module. The numbers on the bottom are the calibration for
    the throttle control.
    By default the deadzone value is 5 away from what was measured on the test bench.
    Min values are 0.
    Max values are 1023.
    
    If your throttle lever has too much of a deadzone at the top or bottom,
    you may lower the min values or raise the max values.
    Alternatively, if your throttle lever isn't quite reaching zero or max,
    you may raise the min values or lower the max values.
  */
  
  #define throttle_min 281
  #define throttle_max 862
  #define throttle_pmin 250
  #define throttle_pmax 769


//|---------------------|
//|   Analog Settings   |
//|---------------------|
  /*
    These values handle the deadzones for all joystick modules as well as 
    the throttle knob on some analog modules.
    Min values are 0.
    Max values are 1023.
    
    If your analog sticks have a deadzone in the center that is too large,
    you may raise deadZone_min and/or lower deadZone_max.
    If your analog sticks have a deadzone in the center that is too small,
    (such as the stick giving input when you aren't touching it) you may
    lower deadZone_min and/or raise deadZone_max.
  
    If the throttle knob has deadzones that are too large, you may lower
    minVolt_ and/or raise maxVolt_.
    If the throttle knob has deadzones that are too small, (such as the
    throttle giving input when it is off, or never reaching 100%), you may
    raise minVolt_ and/or lower maxVolt_.
  */
  
  #define deadZone_min 466
  #define deadZone_max 557
  #define maxVolt_ 1020
  #define minVolt_ 3


//|------------------------------|
//|   Analog Joystick Settings   |
//|------------------------------|
  /*
    These values are for editing the analog control sticks.
  */
  
  #define maxVolt 1023
  #define joystick_center 512
  #define minVolt 0
  #define flip_pitch_axis false
  #define flip_yaw_axis false
  #define flip_roll_axis false
  #define flip_x_axis false
  #define flip_y_axis false
  #define flip_z_axis false


//|------------------------|
//|   Emulation Settings   |
//|------------------------|
  /*
    These values are the inputs for each button in the USC catalog.
    The values here are examples. To change the mapping,
    simply edit the value in the right-most column.
    It is recommended that you use lower case characters.
  
    You may find a list of modifiers and special keys here:
    https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
  */

  // Module_InputName          |         Keyboard Value

  #define Action_Group_1                      '1'
  #define Action_Group_2                      '2'
  #define Action_Group_3                      '3'
  #define Action_Group_4                      '4'
  #define Action_Group_5                      '5'
  #define Action_Group_6                      '6'
  #define Action_Group_7                      '7'
  #define Action_Group_8                      '8'
  #define Action_Group_9                      '9'
  #define Action_Group_10                     '0'
  #define Action_Group_11                     '1'
  #define Action_Group_12                     '2'
  #define Action_Group_13                     '3'
  #define Action_Group_14                     '4'
  #define Action_Group_15                     '5'
  #define Action_Group_16                     '6'
  #define Action_Group_17                     '7'
  #define Action_Group_18                     '8'
  #define Action_Group_19                     '9'
  #define Action_Group_20                     '0'
  #define Action_Group_21                     '1'
  #define Action_Group_22                     '2'
  #define Action_Group_23                     '3'
  #define Action_Group_24                     '4'
  #define Action_Group_25                     '5'
  #define Action_Group_26                     '6'
  #define Action_Group_27                     '7'
  #define Action_Group_28                     '8'
  #define Action_Group_29                     '9'
  #define Action_Group_30                     '0'

  #define Control_Systems_Hold                '1'
  #define Control_Systems_Maneuver            '2'
  #define Control_Systems_Prograde            '3'
  #define Control_Systems_Retrograde          '4'
  #define Control_Systems_Normal              '5'
  #define Control_Systems_AntiNormal          '6'
  #define Control_Systems_RadialOut           '7'
  #define Control_Systems_RadialIn            '8'
  #define Control_Systems_TargetPrograde      '9'
  #define Control_Systems_TargetRetrograde    '0'
  #define Control_Systems_SAS                 't'
  #define Control_Systems_RCS                 'r'

  #define Camera_UI                           KEY_F2
  #define Camera_Screenshot                   KEY_F1
  #define Camera_IVA                          'c'
  #define Camera_CycleCamera                  'v'
  #define Camera_Plus                         '+'
  #define Camera_Minus                        '-'
  #define Camera_Up                           KEY_UP_ARROW
  #define Camera_Down                         KEY_DOWN_ARROW
  #define Camera_Left                         KEY_LEFT_ARROW
  #define Camera_Right                        KEY_RIGHT_ARROW

  #define Executive_Actions_Stage             ' '
  #define Executive_Actions_Abort             KEY_BACKSPACE
  #define Executive_Actions_AG1               '1'
  #define Executive_Actions_AG2               '2'
  #define Executive_Actions_AG3               '3'
  #define Executive_Actions_AG4               '4'
  #define Executive_Actions_AG5               '5'
  #define Executive_Actions_Light             'u'
  #define Executive_Actions_Gear              'g'
  #define Executive_Actions_Hold              '1'
  #define Executive_Actions_SAS               't'
  #define Executive_Actions_RCS               'r'

  #define Time_Pause                          'e'
  #define Time_Save                           's'
  #define Time_Load                           'l'
  #define Time_To_Mnvr                        '1'
  #define Time_Phys_Tw                        'p'
  #define Time_Timewarp_Up                    '.'
  #define Time_Timewarp_Down                  ','
  #define Time_Stop_Tw                        '/'

  #define Navigation_Map                      'm'
  #define Navigation_Cycle_Map_Up             KEY_TAB
  #define Navigation_Cycle_Map_Down           KEY_TAB
  #define Navigation_Map_Return               '`'
  #define Navigation_Nav                      '.'
  #define Navigation_Cycle_Nav                '1'
  #define Navigation_Cycle_Ship_Up            ']'
  #define Navigation_Cycle_Ship_Down          '['
  #define Navigation_To_Mnvr                  '1'
  #define Navigation_Phys_Tw                  KEY_LEFT_ALT
  #define Navigation_Timewarp_Up              '.'
  #define Navigation_Timewarp_Down            ','
  #define Navigation_Stop_Tw                  '/'

  #define Utility_Board                       'b'
  #define Utility_Grab                        'f'
  #define Utility_Jump                        ' '
  #define Utility_Jet                         'r'
  #define Utility_Light                       'u'
  #define Utility_Map                         'm'
  #define Utility_Cycle_Ship                  ']'
  #define Utility_Cycle_Nav                   '1'
  #define Utility_Pause                       KEY_ESC
  #define Utility_Save                        KEY_F5
  #define Utility_Pause                       KEY_F9

  #define EVA_Board                           'b'
  #define EVA_Grab                            'f'
  #define EVA_Jump                            ' '
  #define EVA_Jet                             'r'
  #define EVA_Light                           'u'
  #define EVA_Up                              KEY_LEFT_SHIFT
  #define EVA_Down                            KEY_LEFT_CTRL
  #define EVA_W                               'w'
  #define EVA_A                               'a'
  #define EVA_S                               's'
  #define EVA_D                               'd'

  #define Telemetry_ALVL                      '1'
  #define Telemetry_Mnvr                      '2'
  #define Telemetry_Orbt                      '3'
  #define Telemetry_Fuel                      '4'

  #define Analog_Trim                         ':'
  #define Analog_Reset_Trim                   '?'
  #define Analog_Brakes                       'b'
  #define Analog_Brakes_Lock                  'b'
  #define Analog_Gear                         'g'
  #define Analog_Light                        'u'
  #define Analog_PLN                          '3'
  // RKT mode is not actually an input
  #define Analog_RVR                          '5'
  #define Analog_TRN                          '6'
  #define Analog_ROT                          '7'
  #define Analog_Cruise                       '8'
  #define Analog_Reset_Cruise                 '9'
  #define Analog_Precision_Control            '0'

  #define Throttle_Min_Hold                   '1'
  #define Throttle_PCSN                       '2'

  /*
    Only use below this line if your game does not support joystick controls.
    Please note that this will be a simple on/off digital input rather than
    smooth anaglog controls. For combined Rotation/Translation Analog modules,
    use the Rotation inputs.
  */

  // You can enable keyboard emulation by setting this to true.
  bool Enable_Joystick_Keyboard_Emulation = false;

  #define Rotation_Forward                    'w'
  #define Rotation_Backward                   's'
  #define Rotation_Left                       'a'
  #define Rotation_Right                      'd'
  #define Rotation_Twist_Left                 'q'
  #define Rotation_Twist_Right                'e'
  
  #define Translation_Forward                 'i'
  #define Translation_Backward                'k'
  #define Translation_Left                    'j'
  #define Translation_Right                   'l'
  #define Translation_Twist_Left              'h'
  #define Translation_Twist_Right             'n'
  
  #define Throttle_Forward                    '0'
  
  
  
  































  
