#include <TinyWire.h>
#include <ShiftRegister74HC595.h>

byte own_address = 19;
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
  for(int i = 0; i < 7; i++) {
    if (bytes[0] & 1<<i) {
      sr.set(i, HIGH);
    } else {
      sr.set(i, LOW);
    }
  }
}

void onI2CReceive(int howMany){
  bytes[0] = TinyWire.read();
}
