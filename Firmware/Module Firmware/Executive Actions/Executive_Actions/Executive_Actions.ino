#include <TinyWire.h>

byte own_address = 12;
int x[8] = {};
byte inputs;
int input1 = 4;
int input2 = 3;

void setup() {
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
  x[0] = digitalRead(input1);
  x[1] = digitalRead(input2);
  for(int i = 0; i < 2; i++) {
    bitWrite(inputs, i, x[i]);
  }
}

void onI2CRequest() {
  TinyWire.send(inputs);
}
