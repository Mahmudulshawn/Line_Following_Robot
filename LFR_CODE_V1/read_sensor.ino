void read_black_line() {
  sumOnSensor = 0;
  sensorWeight = 0;
  bitSensor = 0;

  qtr.read(sensorValues);
  for (int i = 0; i < sensorNumber; i++) {

    // if(sensorValues[i] < 300) {
    //   sensorValues[i] = 0;
    // }else if (sensorValues[i] > 300) {
    //   sensorValues[i] = 1000;
    // }

    // if(sensorValues[i] > Reference_Value[i]) {
    //   if(inverseON == 0) { //black line -> Normal Mode
    //    sensorDigital[i] = 1; //black line = 1
    //   }else {
    //     sensorDigital[i] = 0; // black line = 0 (black line - inverse mode)
    //   }
    // }else {
    //   if(inverseON == 0) { //white line - normal mode
    //     sensorDigital[i] = 0; //white line = 0 - normal mode
    //   }else {
    //     sensorDigital[i] = 1; //white line - inverse mode
    //   }
    // }
    sensorDigital[i] = (sensorValues[i] > Reference_Value[i]) ^ inverseON;

    sumOnSensor += sensorDigital[i];
    sensorWeight += sensorDigital[i] * weightValue[i];
    bitSensor += sensorDigital[i] * bitWeight[7 - i];
  }
}

void Bit_Sensor_Show() { // For Debugging Sensor Values For Both Type of Lines.
  read_black_line();

  Serial.print(" | Bit Sensor in Binary: ");

  for(int i = (sensorNumber - 1); i >= 0; i--){
    Serial.print(String(bitRead(bitSensor, i)));
  }

  Serial.println();
}


