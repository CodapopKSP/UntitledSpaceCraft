// Transmissions
if (Ctrl_Sys_Ctrl_Con) {module_transmission(Ctrl_Sys_Ctrl_, Ctrl_Sys_Ctrl, TWO_BYTES, Ctrl_Sys_Dspl_, Ctrl_Sys_Dspl, ONE_BYTE);}

// Enable Action
if (Ctrl_Sys_Ctrl_Con){Ctrl_Sys_Action();}

// Action Results
AutopilotMode SASMode[10] = {
  AP_MANEUVER,
  AP_STABILITYASSIST,
  AP_RETROGRADE,
  AP_PROGRADE,
  AP_ANTINORMAL,
  AP_NORMAL,
  AP_RADIALOUT,
  AP_RADIALIN,
  AP_ANTITARGET,
  AP_TARGET,
};

// Action
void Ctrl_Sys_Action() {
  ControlSys_combinedBytes = Ctrl_Sys_Ctrl[0] + (Ctrl_Sys_Ctrl[1]*256);
  if (ControlSys_combinedBytes != Ctrl_Sys_STATE) {
    Ctrl_Sys_STATE = ControlSys_combinedBytes;

    if (!keyboardEmulation) {
      // Controller is in KSP mode
      for (int i = 0; i < 10; i++) {
        setSimpitAction(Ctrl_Sys_STATE & 1<<i, SASMode[i], Ctrl_Systems_flag[i], simpitSetSASMode);
      }
      setSimpitAction_Switch(Ctrl_Sys_STATE & 1024, SAS_ACTION, Ctrl_Systems_flag[10], simpitActivateAction, simpitDeactivateAction);
      setSimpitAction_Switch(Ctrl_Sys_STATE & 2048, RCS_ACTION, Ctrl_Systems_flag[11], simpitActivateAction, simpitDeactivateAction);
    } else {
      // Controller is in Keyboard Emulation mode
      for (int i = 0; i < 10; i++) {
        setKey(Ctrl_Sys_STATE & 1<<i, Control_Systems_Emulation_Keys[i], Ctrl_Systems_flag[i]);
      }
      setKey_Switch(Ctrl_Sys_STATE & 1024, Control_Systems_SAS, Ctrl_Systems_flag[10]);
      setKey_Switch(Ctrl_Sys_STATE & 2048, Control_Systems_RCS, Ctrl_Systems_flag[11]);
    }
  }
  Ctrl_Sys_LAST = Ctrl_Sys_STATE;
}

// Message Handler
    case SAS_MODE_INFO_MESSAGE:
      if (Ctrl_Sys_Ctrl_Con or EA_Control_Ctrl_Con) {
        if (msgSize == sizeof(SASInfoMessage)) {
          SASInfoMessage mySAS;
          mySAS = parseSASInfoMessage(msg);
          bool stabAssist = (mySAS.currentSASMode==AP_STABILITYASSIST);
          bitWrite(EA_Control_Dspl[0], 3, stabAssist);
          if (ControlSys_combinedBytes & 1024) {
            Ctrl_Sys_Dspl[0] = mySAS.currentSASMode;
          } else {
            Ctrl_Sys_Dspl[0] = 11;
          }
        }
      }
      break;

// Keyboard Emulation
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

// definitions
  const uint8_t Control_Systems_Emulation_Keys[12] = {
    Control_Systems_Maneuver,
    Control_Systems_Hold,
    Control_Systems_Retrograde,
    Control_Systems_Prograde,
    Control_Systems_AntiNormal,
    Control_Systems_Normal,
    Control_Systems_RadialOut,
    Control_Systems_RadialIn,
    Control_Systems_TargetRetrograde,
    Control_Systems_TargetPrograde,
  };