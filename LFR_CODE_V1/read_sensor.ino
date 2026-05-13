void read_black_line() {
  sumOnSensor = 0;
  sensorWeight = 0;
  bitSensor = 0;

  qtr.read(sensorValues);
  for (int i = 0; i < sensorNumber; i++) {
    if (sensorValues[i] > threshold) {
      sensorDigital[i] = 1;
    } else {
      sensorDigital[i] = 0;
    }

    if(sensorValues[i] > Reference_Value[i]) {
      if(inverseON == 0) { //black line -> Normal Mode
       sensorDigital[i] = 1; //black line = 1
      }else {
        sensorDigital[i] = 0; // black line = 0 (black line - inverse mode)
      }
    }else {
      if(inverseON == 0) { //white line - normal mode
        sensorDigital[i] = 0; //white line = 0 - normal mode
      }else {
        sensorDigital[i] = 1; //white line - inverse mode
      }
    }

    // sensorDigital[i] = (sensorValues[i] > Reference_Value[i]) ^ inverseON;

    sumOnSensor += sensorDigital[i];
    sensorWeight += sensorDigital[i] * weightValue[i];
    bitSensor += sensorDigital[i] * bitWeight[7 - i];
  }
}

void Bit_Sensor_Show() { // For Debugging Sensor Values For Both Type of Lines.
  read_black_line();

  for(int i = (sensorNumber - 1); i >= 0; i--){
    Serial.print(String(bitRead(bitSensor, i)));
  }
  switch(bitSensor) {
    // LEFT
    case 0b11110000: direction = LEFT;     break;
    case 0b11111000: direction = LEFT;     break;
    case 0b11111100: direction = LEFT;     break;
    // case 0b11110011: direction = LEFT;     break;

    // RIGHT
    case 0b00001111: direction = RIGHT;    break;
    case 0b00011111: direction = RIGHT;    break;
    case 0b00111111: direction = RIGHT;    break;
    // case 0b11001111: direction = RIGHT;    break;

    // STRAIGHT
    case 0b00111100:
    case 0b00011100:
    case 0b00111000:
    case 0b00011000:
    case 0b00110000:
      direction = STRAIGHT;
      break;

    default:         direction = STRAIGHT; break;
  }

  if(direction == LEFT) {
    Serial.print("LEFT");
  } else if(direction == RIGHT)
  {
   Serial.print("RIGHT");
  } else if(direction == STRAIGHT) {
    Serial.print("STRAIGHT");
  } else {
    Serial.print("NULL");
  }

  Serial.println();
}


