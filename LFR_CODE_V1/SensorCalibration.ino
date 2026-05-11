void calibrateSensor() {
  // Initialize max/min arrays
  for (int i = 0; i < sensorNumber; i++) {
    Max_Value[i] = 0;
    Min_Value[i] = 1024;
  }

  // Define rotation directions for calibration sweeps
  int rotationDirections[][2] = {
    {-1,  1},  // rotate slightly to the left
    { 1, -1},  // rotate slightly to the right
    { 1, -1},  // rotate further right for better coverage
    {-1,  1},  // rotate back left to cover full sensor range
  };

  // Perform calibration sweeps (4 passes)
  for (int step = 0; step < 4; step++) {
    delay(200); // Settle before each new rotation direction

    motor(200 * 0.4 * rotationDirections[step][0],
          200 * 0.4 * rotationDirections[step][1]);

    // Sweep through several readings while rotating
    for (int sweep = 0; sweep < 500; sweep++) {
      qtr.read(sensorValues); // Read all sensors once per sweep tick

      for (int i = 0; i < sensorNumber; i++) {
        Max_Value[i] = max(Max_Value[i], sensorValues[i]);
        Min_Value[i] = min(Min_Value[i], sensorValues[i]);
      }
    }
  }

  stop();

  // Calculate reference values and write to EEPROM once after all sweeps
  for (int i = 0; i < sensorNumber; i++) {
    Reference_Value[i] = (Max_Value[i] + Min_Value[i]) / 2;

    EEPROM.write(i, Reference_Value[i] / 4);
    delay(5);
    EEPROM.write(i + sensorNumber, Max_Value[i] / 4);
    delay(5);
    EEPROM.write(i + (sensorNumber * 2), Min_Value[i] / 4);
    delay(5);
  }
}

void LoadCalibration() {
  Serial.println("=== Loaded Calibration ===");
  Serial.println("IDX | REF  | MAX  | MIN");
  Serial.println("----+------+------+-----");

  for (int i = 0; i < sensorNumber; i++) {
    Reference_Value[i] = EEPROM.read(i)                     * 4;
    Max_Value[i]       = EEPROM.read(i + sensorNumber)      * 4;
    Min_Value[i]       = EEPROM.read(i + (sensorNumber * 2)) * 4;

    Serial.print(" S" + String(i) + " | ");
    Serial.print(String(Reference_Value[i]) + "  | ");
    Serial.print(String(Max_Value[i])       + "  | ");
    Serial.println(String(Min_Value[i]));
  }
  Serial.println("==========================");
}

