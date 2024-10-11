#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 33;
bool x[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
  for(int i = 0; i < 8; i++) {
    x[i] = bitRead(bytes[0], i);
  }
  for(int i = 0; i < 2; i++) {
    x[i+8] = bitRead(bytes[1], i);
  }
  for(int i = 0; i < 10; i++) {
    sr.set(i, x[i]);
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
  bytes[1] = TinyWire.read();
}
