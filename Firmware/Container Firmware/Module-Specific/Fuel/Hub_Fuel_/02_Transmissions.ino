//|-------------------|
//|   Transmissions   |
//|-------------------|

void fuel_transmission(int ctrl_address, int dspl_address, int fuel_register[], int stage_register[]) {

  //Wire.requestFrom(ctrl_address, 2);
  //byte mode = Wire.read();
  //byte brightness = Wire.read();

  byte mode = 0;
  byte brightness = 0;
  mode = constrain(mode, 0, 1);
  brightness = constrain(brightness, 0, 15);

  if (mode) {
    fuel1 = sfuel1;
    fuel2 = sfuel2;
    fuel3 = sfuel3;
    fuel5 = sfuel5;
  }

  fuel1 = test;
  fuel2 = test;
  fuel3 = test;
  fuel4 = test;
  fuel5 = test;
  fuel6 = test;

  fuel1 = constrain(fuel1, 0, 20);
  fuel2 = constrain(fuel2, 0, 20);
  fuel3 = constrain(fuel3, 0, 20);
  fuel4 = constrain(fuel4, 0, 20);
  fuel5 = constrain(fuel5, 0, 20);
  fuel6 = constrain(fuel6, 0, 20);
  
  Wire.beginTransmission(dspl_address);
  Wire.write(fuel1);
  Wire.write(fuel2);
  Wire.write(fuel3); 
  Wire.write(fuel4);
  Wire.write(fuel5);
  Wire.write(fuel6);
  Wire.write(brightness);
  Wire.endTransmission();

  /*
  delay(100);
  Wire.beginTransmission(dspl_address);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0); 
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(brightness);
  Wire.endTransmission();
  delay(50);*/
  
}
