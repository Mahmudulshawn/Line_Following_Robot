void calibrateSensor() {
  for(int i = 0; i < sensorNumber; i++) {
    Max_Value[i] = 0;         //set the max to 0 (lowest possible)
    Min_Value[i] = 1024;      //set the min to 1024 (highest possible)
  }
  //Define rotation directions for calibration sweeps
  int rotationDirections[][2] = {
    {-1, 1}, //rotate slightly to the left
    {1, -1}, //rotate slightly to the right
    {1, -1}, //rotate to the right for better calibration coverage
    {-1, 1}, //rotate left to cover the full sensor range
  };

  //Perform calibration sweeps (4 passes)
  for(int step = 0; step < 4; step++) {
    motor(base_speed * 0.4 * rotationDirections[step][0],
          base_speed * 0.4 * rotationDirections[step][1]);

    // Sweep through several readings while rotating
    for(int sweep = 0; sweep < 500; sweep++) {
      //Read each sensor one by one
      for(int i = 0; i < sensorNumber; i++) {
        qtr.read(sensorValues);

        //Update the max and min values recorded for this sensor
        Max_Value[i] = max(Max_Value[i], sensorValues[i]);
        Min_Value[i] = min(Min_Value[i], sensorValues[i]);
      }
    }
    stop();
    delay(200);

    for (int i = 0; i < sensorNumber; i++) {
      Reference_Value[i] = (Max_Value[i] + Min_Value[i]) / 2.0; //Calculate the mid-point

      EEPROM.write(i, Reference_Value[i] / 4); //Store reference value (divided by 4 because EEPROM can store max 1 byte (0-255))
      delay(5);
      EEPROM.write(i + sensorNumber, Max_Value[i] / 4); //Store max calibrated value
      delay(5);
      EEPROM.write(i + (sensorNumber * 2), Min_Value[i] / 4); //Store min calibrated value
      delay(5);
    }
  }
}

void LoadCalibration() {
  //Print header labels for serial monitor (sensor indices)
  Serial.print("S0: ");
  Serial.print(", S1: ");
  Serial.print(", S2: ");
  Serial.print(", S3: ");
  Serial.print(", S4: ");
  Serial.print(", S5: ");
  Serial.print(", S6: ");
  Serial.print(", S7: ");
  Serial.println();

  //Load the stored calibration data for each sensor
  for(int i = 0; i < sensorNumber; i++) {
    Reference_Value[i] = EEPROM.read(i) * 4;
    Max_Value[i] = EEPROM.read(i) * 4;
    Min_Value[i] = EEPROM.read(i) * 4;

    Serial.print(String(Reference_Value[i]) + ",  "); //Print loaded reference value
  }
  Serial.println();
  
}

