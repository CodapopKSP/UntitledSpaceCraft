#include <TinyWire.h>

byte own_address = 11;
byte abort_;
int input1 = 4;

void setup() {
  pinMode(input1, INPUT);
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
  abort_ = char(digitalRead(input1));
}

void onI2CRequest() {
  TinyWire.send(abort_);
}
