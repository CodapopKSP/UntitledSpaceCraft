#include <Wire.h>
byte x[9] = {};
int add_sub = 0;


//|-------------------|
//|       Main        |
//|-------------------|

void setup() {
  // Connect to Simpit
  Wire.begin();
  Serial.begin(115200);
  Serial.println("ON");
}

void loop() {
  Wire.requestFrom(50, 3);
  x[0] = Wire.read();
  x[1] = Wire.read();
  x[2] = Wire.read();
  int axis1 = (int)x[1] << 8 | (int)x[2];
  if (axis1>500) {
    add_sub = -5;
  } else {
    add_sub = 5;
  }

  Serial.println(x[0]);
  Serial.println(axis1 + add_sub);
  delay(100);
}
