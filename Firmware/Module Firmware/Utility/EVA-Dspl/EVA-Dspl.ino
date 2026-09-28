#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 23;
byte bytes[1] = {0};
ShiftRegister74HC595<2> sr(3, 1, 4);

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onReceive(onI2CReceive);
  for(int i = 0; i < 16; i++) {
    sr.set(i, LOW);
  }
}

void loop() {
  for(int i = 0; i < bytes[0]; i++) {
    sr.set(i, 1);
  }
  for(int i = bytes[0]; i < 10; i++) {
    sr.set(i, 0);
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
}
