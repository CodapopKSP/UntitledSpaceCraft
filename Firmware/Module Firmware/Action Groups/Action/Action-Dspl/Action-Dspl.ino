#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 31;
byte bytes[2] = {0,0};
ShiftRegister74HC595<2> sr(3, 1, 4);

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onReceive(onI2CReceive);
  for(int i = 0; i < 16; i++) {
    sr.set(i, LOW);
  }
}

void loop() {
  int bytes_combined = bytes[0] + (bytes[1]*256);
  for(int i = 0; i < 10; i++) {
    if (bytes_combined & 1<<i) {
      sr.set(i, HIGH);
    } else {
      sr.set(i, LOW);
    }
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
  bytes[1] = TinyWire.read();
}
