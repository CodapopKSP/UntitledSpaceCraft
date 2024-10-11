#include <TinyWire.h>

byte own_address = 50;
int x[8] = {};
byte inputs;
int input1 = 1;
int input2 = 3;
int throttle = 0;

void setup() {
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(A2, INPUT);
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
  x[0] = digitalRead(input1);
  x[1] = digitalRead(input2);
  for(int i = 0; i < 2; i++) {
    bitWrite(inputs, i, x[i]);
  }
  throttle = analogRead(A2);
}

void onI2CRequest() {
  TinyWire.send(inputs);
  TinyWire.send(highByte(throttle));
  TinyWire.send(lowByte(throttle));
}
