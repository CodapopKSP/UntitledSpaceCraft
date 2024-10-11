#include <Wire.h>

int address_ = 19;
int chips = 2;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing...");
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(10);
  digitalWrite(7, HIGH);
  delay(100);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("Beginning LED Test");
  delay(100);
}

void loop() {
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(0);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(1);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(2);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(4);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(8);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(16);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(32);
  Wire.endTransmission();
  delay(250);
  Serial.println("First LED Test");
  Wire.beginTransmission(address_); // transmit to device #8
  Wire.write(64);
  Wire.endTransmission();
  delay(250);
}
