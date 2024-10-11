#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 25;
byte bytes[1] = {0};
ShiftRegister74HC595<2> sr(3, 1, 4);

#define AP_STABILITYASSIST 0
#define AP_PROGRADE 1
#define AP_RETROGRADE 2
#define AP_NORMAL 3
#define AP_ANTINORMAL 4
#define AP_RADIALIN 5
#define AP_RADIALOUT 6
#define AP_TARGET 7
#define AP_ANTITARGET 8
#define AP_MANEUVER 9

int SASMode[10] = {
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

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onReceive(onI2CReceive);
  for(int i = 0; i < 16; i++) {
    sr.set(i, LOW);
  }
}

void loop() {
  for(int i = 0; i < 10; i++) {
    if (bytes[0] == SASMode[i]) {
      sr.set(i, HIGH);
    } else {
      sr.set(i, LOW);
    }
  }
  if (bytes[0] == 11) {
    for(int i = 0; i < 16; i++) {
      sr.set(i, LOW);
    }
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
}
