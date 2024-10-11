#include <TinyWire.h>
#include <ShiftIn.h>

byte own_address = 30;
int x[16] = {};
byte bytes[2] = {};
ShiftIn<2> shift;

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
  shift.begin(4, 5, 3, 1);
}

void loop() {
  shift.update();
  for(int i = 0; i < 16; i++) {
    x[i] = shift.state(i);
  }
  for(int i = 0; i < 8; i++) {
    bitWrite(bytes[0], i, x[i]);
  }
  for(int i = 0; i < 8; i++) {
    bitWrite(bytes[1], i, x[i+8]);
  }
}

void onI2CRequest() {
  TinyWire.send(bytes[0]);
  TinyWire.send(bytes[1]);
}
