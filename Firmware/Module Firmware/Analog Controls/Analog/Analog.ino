#include <TinyWire.h>
#include <ShiftIn.h>

byte own_address = 48;
int x[8] = {};
byte bytes[1] = {};
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
ShiftIn<1> shift;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
  shift.begin(10, 0, 8, 9);
}

void loop() {
  shift.update();
  for(int i = 0; i < 8; i++) {
    x[i] = shift.state(i);
  }
  for(int i = 0; i < 8; i++) {
    bitWrite(bytes[0], i, x[i]);
  }
  axis1 = analogRead(A1);
  axis2 = analogRead(A2);
  axis3 = analogRead(A3);
}

void onI2CRequest() {
  TinyWire.send(bytes[0]);
  TinyWire.send(highByte(axis1));
  TinyWire.send(lowByte(axis1));
  TinyWire.send(highByte(axis2));
  TinyWire.send(lowByte(axis2));
  TinyWire.send(highByte(axis3));
  TinyWire.send(lowByte(axis3));
}
