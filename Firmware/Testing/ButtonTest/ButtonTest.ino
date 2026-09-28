#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing...");
  Wire.begin();
  digitalWrite(7, LOW);
  delay(10);
  digitalWrite(7, HIGH);
  delay(100);
  Serial.println("Beginning Button Test");
  int EA_Control_Ctrl_Con = (sendHandshake(27)!=255);
  delay(100);
  Serial.println(EA_Control_Ctrl_Con);
}

void loop() {
  Serial.println("New Test Round");
  transmit(27, 1);
  delay(100);
}

byte sendHandshake(int address) {
  Wire.requestFrom(address, 1);
  byte connection = Wire.read();
  return connection;
}

void transmit(int address, int bytes) {
  Wire.requestFrom(address, bytes);

  byte bytes_[bytes]; 
  for (int i = 0; i<bytes; i++) {
    bytes_[i] = Wire.read();
  }

  Serial.println();
  for (int i = 0; i<bytes; i++) {
    Serial.print(bytes_[i]);
  }
  Serial.println();
  delay(100);
}
