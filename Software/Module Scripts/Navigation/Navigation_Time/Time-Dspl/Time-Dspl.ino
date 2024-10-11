#include <TinyWire.h>

byte own_address = 21;
byte x = 0;

void setup() {
  TinyWire.begin( own_address );
  TinyWire.onReceive( onI2CReceive );
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop() {
  if (x == 0) {
    digitalWrite(3, LOW);
  } else {
    digitalWrite(3, HIGH);
  }
}

void onI2CReceive(int howMany){
  x = TinyWire.read();
}
