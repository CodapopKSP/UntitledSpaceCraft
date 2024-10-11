#include <TinyWire.h>
#include <ShiftIn.h>

byte own_address = 18;
int x[8] = {};
byte byte_ = {};
ShiftIn<1> shift;

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
  shift.begin(4, 5, 3, 1);
}

void loop() {
  shift.update();
  for(int i = 0; i < 8; i++) {
    x[i] = shift.state(i);
  }
  for(int i = 0; i < 8; i++) {
    bitWrite(byte_, i, x[i]);
  }
}

void onI2CRequest() {
  TinyWire.send(byte_);
}
