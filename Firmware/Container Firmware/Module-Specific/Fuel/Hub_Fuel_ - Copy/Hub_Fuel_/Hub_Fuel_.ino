#include <Wire.h>

int test = 0;

#define Reset 7
#define Fuel_Dspl_ 51
unsigned long lastDebounceTime_b = 0;
unsigned long lastDebounceTime_w = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Reset Module
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  delay(1000);
}

void loop() {
  fuel_transmission();
  test += 1;
  if (test > 20) {
    test = 0;
  }
  Serial.println(test);
  delay(250);
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
}

void fuel_transmission() {
  Wire.beginTransmission(Fuel_Dspl_);
  Wire.write(test);
  Wire.write(test);
  Wire.write(test);
  Wire.write(test);
  Wire.write(test);
  Wire.write(test);
  //Wire.write(0);
  Wire.endTransmission();
}
