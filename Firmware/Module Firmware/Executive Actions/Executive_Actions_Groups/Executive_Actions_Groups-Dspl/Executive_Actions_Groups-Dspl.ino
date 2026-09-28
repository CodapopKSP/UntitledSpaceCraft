#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 17;
byte bytes[1] = {0};
ShiftRegister74HC595<1> sr(3, 1, 4);

void setup() {
  TinyWire.begin(own_address);
  TinyWire.onReceive(onI2CReceive);
  for(int i = 0; i < 8; i++) {
    sr.set(i, LOW);
  }
}

void loop() {
  int bytes_combined = bytes[0];
  for(int i = 0; i < 7; i++) {
    if (i==0) {
      if (bytes_combined & 1<<i) {
        sr.set(i, HIGH);
      } else {
        sr.set(i, LOW);
      }
    } else {
      if (bytes_combined & 1<<i) {
        sr.set(i+1, HIGH);
      } else {
        sr.set(i+1, LOW);
      }
    }
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
}
