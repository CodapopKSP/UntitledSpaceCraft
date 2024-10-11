#include <TinyWire.h>

byte own_address = 47;
bool x[8] = {};
byte bytes[1] = {};
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;


void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(5, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(7, INPUT);
  TinyWire.begin(own_address);
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
  x[0] = digitalRead(5);
  x[1] = digitalRead(8);
  x[2] = digitalRead(9);
  x[3] = digitalRead(10);
  x[4] = digitalRead(7);
  for(int i = 0; i < 5; i++) {
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
